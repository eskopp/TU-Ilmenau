var frameNumber = 0;

var backgroundShader;
var minShader;
var pointShader;
var transformShader;

var dynamicObj;
var midObj;
var gridObj;

function webGLStart() {
  /*============== Creating a canvas ====================*/
  var canvas = document.getElementById("my_Canvas");
  gl = canvas.getContext("webgl");

  // Clear the canvas
  gl.clearColor(1.0, 1.0, 1.0, 1.0);

  // initialize Shaders and Buffers
  backgroundShader = createShaderProgram(minVertexShader, minFragmentShader);
  minShader = createShaderProgram(minVertexShader, minFragmentShader);
  //shaderProgramA = createShaderProgram(basicVertexShader, basicFragmentShader);
  pointShader = createShaderProgram(pointVertexShader, pointFragmentShader);
  transformShader = createShaderProgram(
    translationVertexShader,
    translationFragmentShader
  );

  // initialize Objects with Buffer data
  gridObj = createBackgroundObject();
  dynamicObj = createColorObject([0.5, 0.5], [1.0, 0.5, 0.0], [0]);
  midObj = createColorObject([0.5, 0.5], [1.0, 0.5, 0.0], [0]);
}

function createShaderProgram(vertCode, fragCode) {
  /*================ Shaders ====================*/
  // get vertex shader source code
  // Create a vertex shader object
  // Attach vertex shader source code
  // Compile the vertex shader
  var vertShader = gl.createShader(gl.VERTEX_SHADER);
  gl.shaderSource(vertShader, vertCode);
  gl.compileShader(vertShader);

  //same for fragment-shader
  var fragShader = gl.createShader(gl.FRAGMENT_SHADER);
  gl.shaderSource(fragShader, fragCode);
  gl.compileShader(fragShader);

  // Create a shader program object to store
  // Attach a vertex shader
  // Attach a fragment shader
  // Link both the programs
  // Use the combined shader program object
  var program = gl.createProgram();
  gl.attachShader(program, vertShader);
  gl.attachShader(program, fragShader);
  gl.linkProgram(program);
  return program;
}

/*======== Defining and storing the background geometry ===========*/
function createBackgroundObject() {
  let vertBuffer = gl.createBuffer();
  let tCounter = 0;
  let gridCounter = 0;
  let axisCounter = 0;
  let positions = [
    1.0,
    0.0,
    0.95,
    0.03,
    0.95,
    -0.03, //Triangle
    0.0,
    1.0,
    0.03,
    0.95,
    -0.03,
    0.95, //Triangle
  ];
  tCounter = 6;

  // Grid
  for (let i = -1.0; i < 0.95; i = i + 0.1) {
    positions.push(i, -1.0);
    positions.push(i, 1.0);
    positions.push(-1.0, i);
    positions.push(1.0, i);
    gridCounter += 4;
  }

  // Axis
  positions.push(-1.0, 0.0);
  positions.push(1.0, 0.0);
  positions.push(0.0, -1.0);
  positions.push(0.0, 1.0);
  axisCounter = 4;
  for (let i = -1.0; i < 0.95; i = i + 0.1) {
    positions.push(i, -0.01);
    positions.push(i, 0.01);
    positions.push(-0.01, i);
    positions.push(0.01, i);
    axisCounter += 4;
  }

  // Create an empty buffer object to store position_buffer
  // Bind appropriate array buffer to it
  // Pass the vertex data to the buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, vertBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

  return {
    tStart: 0,
    tLength: tCounter,
    gridStart: tCounter,
    gridLength: gridCounter,
    axisStart: gridCounter + tCounter,
    axisLength: axisCounter,
    vertexBuffer: vertBuffer,
  };
}

/*======== Create default Object to storing the geometry ===========*/
function createColorObject(positions, colors, indices) {
  // Create an empty buffer object to store position_buffer
  // Bind appropriate array buffer to it
  // Pass the vertex data to the buffer
  // Point an attribute to the currently bound VertexBufferObject (VBO)
  // Enable the attribute
  var positionBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

  // Same for ColorBuffer
  var colorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);

  // Create an empty buffer object to store Index buffer
  // Bind appropriate array buffer to it
  // Pass the vertex data to the buffer
  var indexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(
    gl.ELEMENT_ARRAY_BUFFER,
    new Uint16Array(indices),
    gl.STATIC_DRAW
  );

  return {
    size: positions.length / 2,
    vertBuffer: positionBuffer,
    colorBuffer: colorBuffer,
    indexBuffer: indexBuffer,
  };
}

function updateObjData(positions, colors) {
  gl.bindBuffer(gl.ARRAY_BUFFER, dynamicObj.vertBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.DYNAMIC_DRAW);

  gl.bindBuffer(gl.ARRAY_BUFFER, dynamicObj.colorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.DYNAMIC_DRAW);

  dynamicObj.size = positions.length / 2;
}

function updateMidData(positions, colors) {
  gl.bindBuffer(gl.ARRAY_BUFFER, midObj.vertBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.DYNAMIC_DRAW);

  gl.bindBuffer(gl.ARRAY_BUFFER, midObj.colorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.DYNAMIC_DRAW);

  midObj.size = positions.length / 2;
}

function renderBackground() {
  // Clear the color buffer bit
  gl.clear(gl.COLOR_BUFFER_BIT);

  // Use ShaderProgramm
  gl.useProgram(backgroundShader);

  // Bind vertice Buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, gridObj.vertexBuffer);
  gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(0);

  //uniform
  let color = gl.getUniformLocation(backgroundShader, "color");
  gl.uniform3f(color, 0.8, 0.8, 0.8);

  // draw grid
  gl.drawArrays(gl.LINES, gridObj.gridStart, gridObj.gridLength);

  // change color
  gl.uniform3f(color, 0.0, 0.0, 0.0);

  // draw axis
  gl.drawArrays(gl.LINES, gridObj.axisStart, gridObj.axisLength);
  // draw arrows
  gl.drawArrays(gl.TRIANGLES, gridObj.tStart, gridObj.tLength);
}

function renderPoints() {
  gl.useProgram(pointShader);
  gl.bindBuffer(gl.ARRAY_BUFFER, midObj.vertBuffer);
  gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(0);

  gl.bindBuffer(gl.ARRAY_BUFFER, midObj.colorBuffer);
  gl.vertexAttribPointer(1, 3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(1);

  gl.drawArrays(gl.POINTS, 0, midObj.size);
  //gl.drawArrays(gl.TRIANGLES, 0, dynamicObj.size);
}

function renderLines() {
  gl.useProgram(minShader);
  gl.bindBuffer(gl.ARRAY_BUFFER, dynamicObj.vertBuffer);
  gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(0);

  gl.drawArrays(gl.LINE_LOOP, 0, dynamicObj.size); //LINE_STRIP
}

function renderTransformedPoints(matrix) {
  gl.useProgram(transformShader);
  gl.bindBuffer(gl.ARRAY_BUFFER, dynamicObj.vertBuffer);
  gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(0);
  let translation = gl.getUniformLocation(transformShader, "translation");
  gl.uniformMatrix3fv(translation, false, matrix);

  gl.drawArrays(gl.LINE_LOOP, 0, dynamicObj.size);
  //gl.drawArrays(gl.POINTS, 0, dynamicObj.size);
  //gl.drawArrays(gl.TRIANGLES, 0, dynamicObj.size);
}
