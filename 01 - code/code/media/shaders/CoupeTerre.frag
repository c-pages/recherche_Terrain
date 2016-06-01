#version 120

uniform sampler2D   texture;
uniform     vec2 origin;


void main() {

    // hachures
    vec4    color       = gl_Color;
    vec2    pos         = gl_FragCoord.xy;
    float   colHachures = .2;
    float   colContour  = .8;
    vec4    hachure     = vec4(color.x + colHachures, color.y + colHachures, color.z + colHachures,1.);
    vec4    contour     = hachure; //vec4(colContour,colContour,colContour,1.);

    int     espacement  = 10;
    float   epaisseur   = 1;
    vec4    pixel       = texture2D(texture, gl_TexCoord[0].xy);

    vec4    textureApresHachures;
    if ( mod ( pos.x + origin.x - pos.y + origin.y, espacement ) < epaisseur )
        textureApresHachures = pixel * hachure;
    else
        textureApresHachures = pixel * color ;






    // contour
    float       edge_threshold = .0001;



    const float offset = 1.0 / (4096.0*2);
    vec2 offx = vec2(offset, 0.0);
    vec2 offy = vec2(0.0, offset);

    vec4 hEdge = texture2D(texture, gl_TexCoord[0].xy - offy)        * -2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offy)        *  2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * -1.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx + offy) *  1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * -1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx + offy) *  1.0;

    vec4 vEdge = texture2D(texture, gl_TexCoord[0].xy - offx)        *  2.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx)        * -2.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) *  1.0 +
                 texture2D(texture, gl_TexCoord[0].xy - offx + offy) * -1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) *  1.0 +
                 texture2D(texture, gl_TexCoord[0].xy + offx + offy) * -1.0;



    vec3 result = sqrt(hEdge.rgb * hEdge.rgb + vEdge.rgb * vEdge.rgb);
    float edge = length(result);


    if (edge > (edge_threshold * 8.0))
        gl_FragColor = contour;
    else
        gl_FragColor = textureApresHachures;




}


