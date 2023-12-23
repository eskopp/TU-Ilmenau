var minVertexShader = `
	attribute vec3 vertex_position;
	
	void main(void) {
		gl_Position = vec4(vertex_position, 1.0);
	}
`;

var basicVertexShader = `
	attribute vec3 vertex_position;
	attribute vec3 vertex_color;
		
	//--> Pass to fragment-shader
	varying vec3 fragment_color;
	
	void main(void) {
		fragment_color = vertex_color;
		gl_Position = vec4(vertex_position, 1.0);
	}
`;

var pointVertexShader = `
	attribute vec3 vertex_position;
	
	void main(void) {
		gl_PointSize = 16.0;
		gl_Position = vec4(vertex_position, 1.0);
	}
`;

var translationVertexShader = `
	attribute vec2 vertex_position;
		
	uniform mat3 translation;	
	
	void main(void) {
		gl_PointSize = 16.0;
		vec3 transPos = translation * vec3(vertex_position,1.0);
		gl_Position = vec4(transPos, 1.0);
	}
`;
