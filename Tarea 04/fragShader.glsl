#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

mat2 scale(vec2 scale){
    return mat2(scale.x,0.0,0.0,scale.y);
}
mat2 rotate(float angle){
    return mat2(cos(angle),-sin(angle),sin(angle),cos(angle));
}
float rectangleShape(vec2 position,vec2 scale){
    scale=vec2(0.5)-scale*0.5;
    vec2 shaper=vec2(step(scale.x,position.x),step(scale.y,position.y));
    shaper*=vec2(step(scale.x,1.0-position.x),step(scale.y,1.0-position.y));
    return shaper.x*shaper.y;
}
void main(){
    vec2 coord=gl_FragCoord.xy/u_resolution;
    //color
    vec3 color=vec3(0.0235, 0.2549, 0.2431);
    //rotate
    coord-=vec2(0.5);
    coord=rotate(sin(u_time)*2)*coord;
    coord+=vec2(0.5);
    //scale
    coord-=vec2(0.5);
    coord=scale(vec2(sin(u_time)+2.0))*coord;
    coord+=vec2(0.5);
    //translate
    vec2 translate=vec2(sin(u_time/5.0),cos(u_time/5.0));
    coord+=translate*0.5;
    //shape
    color*=vec3(rectangleShape(coord,vec2(0.3,0.3)));    
    gl_FragColor=vec4(color,1.0);
}