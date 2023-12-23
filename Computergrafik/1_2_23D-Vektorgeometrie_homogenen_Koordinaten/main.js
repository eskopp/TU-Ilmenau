var loadNow_jsDefinitionForMatrixA = false;

function mainInit() {
  // Init WebGL settings
  webGLStart();

  matrixA_inputToCode();

  // Start Renderloop
  mainRenderer();
}

function matrixA_inputToCode() {
  let js = "";
  for (let i = 0; i < 9; i++)
    js += "matrixA[" + i + "] = " + matAElements[i].value + ";\n";
  matADefJsCode.value = js;
}

function mainRenderer() {
  // Clear Screen and Render Grid
  renderBackground();

  // model points
  let modelPointNum = 5;
  let modelCoords_C = [];
  let colorValues = [];
  let midPoint = [0, 0];
  for (let i = 0; i < modelPointNum; i++) {
    //Position
    modelCoords_C.push(parseFloat(modelElements[3 * i].value));
    modelCoords_C.push(parseFloat(modelElements[3 * i + 1].value));
    //Color
    colorValues.push(0, 0, 0); // simply black now
    // calc midpoint
    midPoint[0] += modelCoords_C[2 * i];
    midPoint[1] += modelCoords_C[2 * i + 1];
  }
  midPoint[0] /= modelPointNum;
  midPoint[1] /= modelPointNum;

  // Update data
  updateObjData(modelCoords_C, colorValues);
  updateMidData(midPoint, [0, 0, 0]);

  // Render simple Points
  renderPoints();
  renderLines();

  //----------------------------------------------------------//
  // Reading matrix A
  let matrixA = new MyMat();
  if (!loadNow_jsDefinitionForMatrixA) {
    for (let i = 0; i < 9; i++) matrixA.push(matAElements[i].value);
  } else {
    let jsMA = matADefJsCode.value;
    eval(jsMA);

    for (let i = 0; i < 9; i++) matAElements[i].value = matrixA[i];

    loadNow_jsDefinitionForMatrixA = false;
  }

  //----------------------------------------------------------//
  // Matrix Multiplication
  let matrixB = new MyMat(); // homog. coords

  // Model as Matrix
  for (let i = 0; i < modelPointNum * 2; i = i + 2) {
    matrixB.push(modelCoords_C[i]);
    matrixB.push(modelCoords_C[i + 1]);
    matrixB.push(1); // w
  }

  // transformed model = matrixA * model
  let matrixRes = matrixA.mulMat(matrixB);

  // Render Points transformed by Matrix
  renderTransformedPoints(matrixA.getValues());

  // Render manuell Transformed Point
  updateMidData(matrixA.mulPoint(midPoint), [0.0, 0.0, 0.0]);
  renderPoints();

  //----------------------------------------------------------//
  // Increase Framecounter
  frameNumber++;

  // update Html inputs
  // document.getElementById('text').innerHTML = frameNumber;
  for (let i = 0; i < matResElements.length; i++) {
    matResElements[i].value = matrixRes[i].toFixed(2);
  }

  //Renderloop = repeated request for mainRenderer
  requestAnimationFrame(mainRenderer);
}
