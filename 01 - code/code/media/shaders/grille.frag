#version 120

uniform sampler2D   texture;
uniform     vec2 origin;

void main() {

    vec4    color       = gl_Color;
    vec2    pos         = gl_FragCoord.xy;
    float   col         = .8;
    int     espacement  = 20;
    float   epaisseur   = 1;
    vec4    hachure     = vec4(col,col,col,1.);
    vec4    pixel       = texture2D(texture, gl_TexCoord[0].xy);


    if ( mod ( pos.x + origin.x , espacement ) < epaisseur
    ||   mod ( pos.y - origin.y , espacement ) < epaisseur )
        gl_FragColor = pixel * hachure;
    else
        gl_FragColor = color * pixel;

}


