var minFragmentShader = `
	precision mediump float; //needed for compatibillity
		
	uniform vec3 color;
		
	void main(void) {
        gl_FragColor = vec4(color, 1.0);
    } 
`;

var basicFragmentShader = `
	precision mediump float; //needed for compatibillity
		
	//<-- received from vertex-shader
	varying vec3 fragment_color;
		
	void main(void) {
        gl_FragColor = vec4(fragment_color, 1.0);
    } 
`;

var pointFragmentShader = `
	precision mediump float; 
			
	void main(void) {
		vec2 coord = gl_PointCoord - vec2(0.5);  //from [0,1] to [-0.5,0.5]
		if(length(coord) > 0.5)                  //outside of circle radius?
			discard;
			
        gl_FragColor = vec4(0,0,0, 1.0);
    } 
`;

var translationFragmentShader = `
	precision mediump float; //needed for compatibillity set float precision to -2^14 to 2^14
				
	void main(void) {			
        gl_FragColor = vec4(0.0,0.0,0.0, 1.0);
    } 
`;
