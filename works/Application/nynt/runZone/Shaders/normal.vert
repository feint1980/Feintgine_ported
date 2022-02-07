#version 100 
//The vertex shader operates on each vertex
//input data from the VBO. Each vertex is 2 floats

#define in attribute
#define out varying

//#define mediump 
in mediump vec2 vertexPosition;
in mediump vec4 vertexColor;
in mediump vec2 vertexUV;


out mediump vec2 fragmentPosition;
out mediump vec4 fragmentColor;
out mediump vec2 fragmentUV;

uniform mediump float fadeout;

uniform mediump mat4 P;

void main() {
    //Set the x,y position on the screen
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    //the z position is zero since we are in 2D
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vec4(vec3(vertexColor.x , vertexColor.y , vertexColor.z ) , vertexColor.w* fadeout) ;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}
