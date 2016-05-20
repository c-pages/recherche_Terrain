#version 120

uniform sampler2D   texture;


void main() {

    vec4    color       = gl_Color;
    vec2    pos         = gl_FragCoord.xy;
    float   col         = 1.5;
    int     espacement  = 20;
    float   epaisseur   = 2;
    vec4    hachure     = vec4(col,col,col,1.);
    vec4    pixel       = texture2D(texture, gl_TexCoord[0].xy);


    if ( mod ( pos.x +pos.y, espacement ) < epaisseur )
        gl_FragColor = pixel * hachure;
    else
        gl_FragColor = pixel * color ;

}


