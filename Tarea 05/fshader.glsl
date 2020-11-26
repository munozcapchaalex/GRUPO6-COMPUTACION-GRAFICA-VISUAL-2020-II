#version 430 core

layout(location=0) out vec4 color;
uniform vec3 circle;

void main(){
	color = vec4(circle, 1.0);
}
