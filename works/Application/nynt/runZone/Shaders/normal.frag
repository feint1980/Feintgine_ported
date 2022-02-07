#version 100 
//The fragment shader operates on each pixel in a given polygon

//#define mediump 

#define in varying
#define out varying

in mediump vec2 fragmentPosition;
in mediump vec4 fragmentColor;
in mediump vec2 fragmentUV;

//This is the 3 component float vector that gets outputted to the screen
//for each pixel.
//out mediump vec4 color;

uniform sampler2D mySampler;


void main() {

    
    //mediump vec4 textureColor = texture2D(mySampler, fragmentUV);
    
   
   // gl_FragColor = (fragmentColor * textureColor);
   gl_FragColor = fragmentColor * texture2D(mySampler, fragmentUV) + vec4(.05f);
   //color = vec4(255,255,0,255);


}
