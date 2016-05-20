#version 120

uniform sampler2D   texture;
uniform vec4        rectMasque;
uniform bool        aTexture    = true;


void main() {

    // la couleur du rectangle (FillColor)
    vec4 color = gl_Color;
    vec2 pos   = gl_FragCoord.xy;

    vec4 masque;
    if ( pos.x < rectMasque.x
    ||   pos.x > rectMasque.x + rectMasque.z
    ||   pos.y < rectMasque.y - rectMasque.w
    ||   pos.y > rectMasque.y )
        masque = vec4(0.,0.,0.,0.);
    else
        masque = vec4(1.,1.,1.,1.);


    if ( aTexture ) {
        // la couleur du pixel de la texture
        vec4 pixel = texture2D(texture, gl_TexCoord[0].st);

        gl_FragColor = pixel * color * masque;
    } else {

        gl_FragColor = color * masque;
    }

}


