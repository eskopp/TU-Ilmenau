// javac FwdTrafoExa.java; java FwdTrafoExa
// javac FwdTrafoExa.java; java FwdTrafoExa greyBunny64.pgm 8
// javac FwdTrafoExa.java; java FwdTrafoExa bwwb.pgm 128

import java.io.File;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileInputStream;
import java.io.EOFException;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.io.IOException;
import java.io.FileOutputStream;

public class FwdTrafoExa {

    public static int bigFact = 8;
    public static String action = "r45";
    public static boolean dbg = false;
    public static Pattern pat_i1 = Pattern.compile("\\s*([0-9]+)\\s*");
    public static Pattern pat_i2 = Pattern.compile("\\s*([0-9]+)\\s+([0-9]+)\\s*");

    public static Pattern pat_action = Pattern.compile("\\s*(r|s)((?:|\\+|-)[0-9]+)");

    public static void help(String h) {
        System.out
                .println("# FwdTrafoExa: Generate examples for problems of forward transformation of 2D- pixel images");
        System.out.println("#     " + h);
        System.out.println("#     Usage:   java FwdTrafoExa [<pgmFileName> [<outputPixelScalingFactor> [<trafo>]]]");
        System.out.println("#     Example: java FwdTrafoExa greyBunny64.pgm 8 r45");
        System.exit(-1);
    }

    public static void main(String[] a) {
        dbg = true;

        String fnImg = "greyBunny64.pgm";

        if (a.length > 0)
            fnImg = a[0];
        if (!new File(fnImg).exists())
            help("Error: input file " + fnImg + " does not exist!");

        if (a.length > 1) {
            try {
                bigFact = Integer.parseInt(a[1]);
            } catch (Exception e) {
                help("Error: parameter 2 must be an integer value, but you gave:" + a[1]);
            }
        }

        if (a.length > 2)
            action = a[2];
        if (!pat_action.matcher(action).matches())
            help("Error: action " + action + " is not a valid action");

        if (dbg)
            System.out.println(
                    "# FwdTrafoExa: Generate examples for problems of forward transformation of 2D- pixel images");

        String img1 = getFileContent(fnImg);
        int[][] pix1 = getPixFromPgmP2(img1);

        String fnBas = fnImg.substring(0, fnImg.indexOf("."));
        String fnOri = fnBas + "_original.ppm";
        String fnBwd = fnBas + "_" + action + "_bwd.ppm";
        String fnFwd = fnBas + "_" + action + "_fwd.ppm";

        writeToFile(fnOri, pixToP3(pix1));
        exec("convert " + fnOri + " " + fnBas + "_original.png");
        writeToFile(fnBwd, pixToP3(action_bwd(pix1)));
        exec("convert " + fnBwd + " " + fnBas + "_" + action + "_bwd.png");
        writeToFile(fnFwd, pixToP3(action_fwd(pix1)));
        exec("convert " + fnFwd + " " + fnBas + "_" + action + "_fwd.png");
    }

    public static int[][] action_fwd(int[][] p) {
        return action(p, true);
    }

    public static int[][] action_bwd(int[][] p) {
        return action(p, false);
    }

    public static int[][] action(int[][] p, boolean fwd) {
        Matcher mtc = pat_action.matcher(action);
        if (!mtc.matches())
            return null;

        int param = 0;
        try {
            param = Integer.parseInt(mtc.group(2));
        } catch (Exception e) {
        }
        switch (mtc.group(1)) {
            case "r":
                return rotDeg_Fwd_or_Bwd(p, param, fwd);
            case "s":
                return scale_Fwd_or_Bwd(p, param, fwd);
        }
        return null;
    }

    public static int[][] scale_Fwd_or_Bwd(int[][] p, int f, boolean fwd) {
        int ih = p.length;
        int iw = p[0].length;
        int zh = f * ih;
        int zw = f * iw;
        int[][] r = new int[zh][zw];

        if (fwd) {
            for (int y = 0; y < ih; y++) {
                for (int x = 0; x < iw; x++) {
                    int u = x, v = y;
                    switch (1) {
                        case 0: // copy only (as test case)
                            u = x;
                            v = y;
                            break;

                        case 1: // simply scale according to the orign
                            u = f * x;
                            v = f * y;
                            break;
                    }

                    writeVal(r, u, v, zw, zh, p[y][x]); // may be no info transfered fwd to a point -> 0 is kept -> bad
                                                        // -> red
                }
            }

            // if fwd is true we want to "recolor" some red areas as green (those where no
            // info would be available)
            // and only let those red, where we could have info but it was not used because
            // of fwd propagation -> fill Q with bwd pixels
            int[][] Q = scale_Fwd_or_Bwd(p, f, !fwd);
            for (int y = 0; y < ih; y++)
                for (int x = 0; x < iw; x++)
                    if (r[y][x] == 0 && Q[y][x] == -1) // would be red, but can be green
                        r[y][x] = -2;
        } else {
            for (int v = 0; v < zh; v++) {
                for (int u = 0; u < zw; u++) {
                    int x = u, y = v;
                    switch (1) {
                        case 0: // copy only (as test case)
                            x = u;
                            y = v;
                            break;

                        case 1: // simply scale according to the orign
                            x = u / f;
                            y = v / f;
                            break;
                    }

                    r[v][u] = readVal(p, x, y, iw, ih); // may set -1 -> ok, because there was no source -> green
                }
            }
        }

        return r;
    }

    public static int[][] rotDeg_Fwd_or_Bwd(int[][] p, int deg, boolean fwd) {
        int ih = p.length;
        int iw = p[0].length;
        int[][] r = new int[ih][iw];

        // rotation around the origin needs cos and sin
        double rad = (fwd ? 1 : -1) * deg * Math.PI / 180; // the sign depends on the direction!
        double c = Math.cos(rad);
        double s = Math.sin(rad);

        // coeff. for rot arround the middle (a=iw/2 and b=ih/2)
        // | 1 0 -a
        // | 0 1 -b
        // | 0 0 1
        // --------+---------
        // c -s 0 | c -s -ac+bs
        // s c 0 | s c -as-bc
        // 0 0 1 | 0 0 1
        // --------+---------
        // 1 0 a | c -s a-ac+bs
        // 0 1 b | s c b-as-bc
        // 0 0 1 | 0 0 1
        double a = iw / 2.0;
        double b = ih / 2.0;
        double rm1 = c;
        double rm2 = -s;
        double rm3 = a - a * c + b * s;
        double rm4 = s;
        double rm5 = c;
        double rm6 = b - a * s - b * c;

        for (int y = 0; y < ih; y++) {
            for (int x = 0; x < iw; x++) {
                int u = x, v = y;
                switch (3) {
                    case 0: // copy only (as test case)
                        u = x;
                        v = y;
                        break;

                    case 1: // simply rotate around the orign
                        u = (int) (c * x - s * y);
                        v = (int) (s * x + c * y);
                        break;

                    case 2: // rotate around the middle of the image, cut digits after decimal point
                        u = (int) (rm1 * x + rm2 * y + rm3);
                        v = (int) (rm4 * x + rm5 * y + rm6);
                        break;

                    case 3: // rotate around the middle of the image + round (select int which is nearest)
                        u = (int) (rm1 * x + rm2 * y + rm3 + .5);
                        v = (int) (rm4 * x + rm5 * y + rm6 + .5);
                        break;
                }

                if (fwd)
                    writeVal(r, u, v, iw, ih, p[y][x]); // may be no info transfered fwd to a point -> 0 is kept -> bad
                                                        // -> red
                else
                    r[y][x] = readVal(p, u, v, iw, ih); // may set -1 -> ok, because there was no source -> green
            }
        }

        // if fwd is true we want to "recolor" some red areas as green (those where no
        // info would be available)
        // and only let those red, where we could have info but it was not used because
        // of fwd propagation -> fill Q with bwd pixels
        if (fwd) {
            int[][] Q = rotDeg_Fwd_or_Bwd(p, deg, !fwd);
            for (int y = 0; y < ih; y++)
                for (int x = 0; x < iw; x++)
                    if (r[y][x] == 0 && Q[y][x] == -1) // would be red, but can be green
                        r[y][x] = -2;
        }

        return r;
    }

    public static int readVal(int[][] p, int x, int y, int iw, int ih) {
        if (x < 0 || x >= iw || y < 0 || y >= ih)
            return -1;
        return p[y][x];
    }

    public static void writeVal(int[][] p, int x, int y, int iw, int ih, int val) {
        if (x < 0 || x >= iw || y < 0 || y >= ih)
            return;
        p[y][x] = val;
    }

    public static String pixToP3(int[][] pix) {
        StringBuilder ret = new StringBuilder();

        if (pix == null)
            return "Error: pix was null";

        int ih = pix.length;
        if (ih < 1)
            return "Error: pix height is 0";

        int iw = -1;
        for (int y = 0; y < ih; y++) {
            if (pix[y] == null)
                return "Error: pix[" + y + "] is null";
            if (pix[y].length < 1)
                return "Error: pix[" + y + "].length is 0";
            if (iw < 0)
                iw = pix[y].length;
            else if (iw != pix[y].length)
                return "Error: pix[" + y + "].length is " + pix[y].length + ", but we found a width=" + iw + " before!";
        }

        ret.append("P3\n").append(iw * bigFact).append(" ").append(ih * bigFact).append(" 255\n");
        for (int y = ih - 1; y >= 0; y--) {
            for (int yRep = 0; yRep < bigFact; yRep++) {
                for (int x = 0; x < iw; x++) {
                    for (int xRep = 0; xRep < bigFact; xRep++) {
                        int v = pix[y][x];
                        if (v <= 0)
                            ret.append(v == -1 ? "  0 128   0 " : // RGB: dark green "error code" for no info readable
                                                                  // -> (ok)
                                    v == -2 ? "  0   0 128 " : // RGB: dark blue "error code" for fwd gap where it must
                                                               // bee
                                            "255   0   0 "); // RGB: red as error code for unnecess. fwd gap
                        else
                            ret.append(v).append(" ").append(v).append(" ").append(v).append(" ");
                    }
                }
                ret.append("\n");
            }
        }

        return ret.toString();
    }

    public static int[][] getPixFromPgmP2(String img) {
        String[] lines = img.split("\n");
        if (lines.length < 4) {
            System.out.println("Error: Too few lines!");
            return null;
        }
        if (!lines[0].trim().equals("P2")) {
            System.out.println("Error: First line must be P2");
            return null;
        }
        Matcher mtc = pat_i2.matcher(lines[1]);
        if (!mtc.matches()) {
            System.out.println("Error: line 2 must consist of 2 integer numbers");
            return null;
        }
        int iw = 0;
        try {
            iw = Integer.parseInt(mtc.group(1));
        } catch (Exception e) {
        }
        int ih = 0;
        try {
            ih = Integer.parseInt(mtc.group(2));
        } catch (Exception e) {
        }
        if (dbg)
            System.out.println("# wxh : " + iw + "x" + ih);

        mtc = pat_i1.matcher(lines[2]);
        if (!mtc.matches()) {
            System.out.println("Error: line 3 must be an integer number");
            return null;
        }

        int li = 3;
        int[][] r = new int[ih][iw];
        for (int y = 0; y < ih; y++) {
            mtc = pat_i1.matcher(lines[li++]);
            for (int x = 0; x < iw; x++) {
                if (!mtc.find()) {
                    System.out.println(
                            "Error: too few values in line " + li + " (" + iw + " needed, but only " + x + " found)");
                    return null;
                }
                try {
                    r[ih - 1 - y][x] = Integer.parseInt(mtc.group(1));
                } catch (Exception e) {
                }
            }
        }

        return r;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static public String exec(String cmd) {
        return exec(cmd, true, false, false);
    }

    static public String exec(String cmd, boolean inShell) {
        return exec(cmd, inShell, false, false);
    }

    static public String exec(String cmd, boolean inShell, boolean errStr, boolean dbg) {
        if (dbg)
            System.out.println(cmd);

        String ret = "";
        try {
            Process p = null;
            if (inShell) {
                String sh = "/bin/sh";
                String cop = "-c";
                String[] cis = new String[] { sh, cop, cmd };
                p = Runtime.getRuntime().exec(cis);
            } else
                p = Runtime.getRuntime().exec(cmd);

            BufferedReader in = new BufferedReader(new InputStreamReader(errStr ? p.getErrorStream()
                    : p.getInputStream()));

            for (String s; (s = in.readLine()) != null;)
                ret += s + "\n";
        }

        catch (Exception e) {
            ret = "Problem calling: " + cmd +
                    "\n until here we got :" + ret;
        }
        return ret;
    }

    public static String getFileContent(String fileName) {
        return getFileContent(fileName, "UTF8");
    }

    public static String getFileContent(String fileName, String fileEncoding) {
        StringBuilder ret = new StringBuilder();
        try {
            // BufferedReader in = new BufferedReader (new FileReader(fileName)); problems
            // with old tomcat on dmg3
            BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream(fileName), fileEncoding)); // theEncoding
            try {
                String tmp;
                while ((tmp = in.readLine()) != null) {
                    if (ret.length() > 0) {
                        ret.append("\n");
                    }
                    ret.append(tmp);
                }
            } catch (EOFException eof) {
            } finally {
                in.close();
            }
            return ret.toString();
        } catch (Exception e) {
        }

        return null;
    }

    final static public String theEncoding = "UTF-8"; // "ISO-8859-1";

    static public byte[] sb(String s) {
        return sb(s, theEncoding);
    }

    static public byte[] sb(String s, String encoding) {
        try {
            return s.getBytes(encoding);
        } catch (Exception e) {
            return s.getBytes();
        }
    }

    public static boolean writeToFile(String fileName, String content) {
        return writeToFile(fileName, content, false);
    }

    public static boolean writeToFile(String fileName, String content, boolean append) {
        File oFile = new File(fileName);
        // create the missing parent paths (if there is one)
        if (oFile.getParentFile() != null && !oFile.getParentFile().exists())
            oFile.getParentFile().mkdirs();
        FileOutputStream fos = null;
        try {
            fos = new FileOutputStream(oFile, append);
            fos.write(sb(content));
        } catch (IOException e) {
            System.out.println("Problem writing " + oFile.getName() + "  " + e + "  " + e.getMessage());
            return false;
        } finally {
            try {
                if (fos != null)
                    fos.close();
            } catch (IOException e) {
            }
        }
        return true;
    }

}
