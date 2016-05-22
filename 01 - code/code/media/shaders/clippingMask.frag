#version 120

uniform sampler2D   texture;
uniform vec4        rectMasque  = vec4 ( -1.,-1.,-1.,-1. );
uniform bool        aTexture    = false;


void main() {


    // la couleur du rectangle (FillColor)
    vec4 color = gl_Color;
    vec2 pos   = gl_FragCoord.xy;

    vec4 masque = vec4(0.,0.,0.,0.);

    if ( rectMasque  != vec4 (-1.,-1.,-1.,-1.) ){
        if ( pos.x >= rectMasque.x -1
        &&   pos.x <= rectMasque.x + rectMasque.z +1
        &&   pos.y <= rectMasque.y +1
        &&   pos.y >= rectMasque.y - rectMasque.w -1
        )
            masque = vec4(1.,1.,1.,1.);
    } else masque = vec4(1.,1.,1.,1.);


    if ( aTexture ) {
        // la couleur du pixel de la texture
        vec4 pixel = texture2D(texture, gl_TexCoord[0].st);

//        gl_FragColor = pixel * color;
        gl_FragColor = pixel * color * masque;
    } else {

//        gl_FragColor = color;
        gl_FragColor = color * masque;
    }

//    gl_FragColor = color * texture2D(texture, gl_TexCoord[0].st);

}


