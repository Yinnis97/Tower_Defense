#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 resolution;
uniform float time;


void main() 
{
	vec2 st = gl_FragCoord.xy/resolution;
	
	gl_FragColor = vec4(0.0,st.y,0.3,1.0);
}

