#version 120

uniform sampler2D texture;
uniform float blur_radius;

void main()
{
    vec2 offx = vec2(blur_radius, 0.0);
    vec2 offy = vec2(0.0, blur_radius);





        /////// 5x5 //////////
    const int largeurTab = 5;
    const int tailleTab = largeurTab * largeurTab;

 float tableau[ tailleTab ]=float[](    0.002052,	0.010999	,0.019199	,0.010999	,0.002052,
                                        0.010999,	0.05895	    ,0.102898	,0.05895	,0.010999,
                                        0.019199,	0.102898	,0.179611	,0.102898	,0.019199,
                                        0.010999,	0.05895	    ,0.102898	,0.05895	,0.010999,
                                        0.002052,	0.010999	,0.019199	,0.010999	,0.002052   );





/*
    /////// 7x7 //////////
    const int largeurTab = 7;
    const int tailleTab = largeurTab * largeurTab;


 float tableau[ tailleTab ]=float[](    0.000007	,0.000121	,0.000649	,0.001133	,0.000649	,0.000121	,0.000007,
                                        0.000121	,0.00203	,0.010881	,0.018993	,0.010881	,0.00203	,0.000121,
                                        0.000649	,0.010881	,0.058318	,0.101795	,0.058318	,0.010881	,0.000649,
                                        0.001133	,0.018993	,0.101795	,0.177686	,0.101795	,0.018993	,0.001133,
                                        0.000649	,0.010881	,0.058318	,0.101795	,0.058318	,0.010881	,0.000649,
                                        0.000121	,0.00203	,0.010881	,0.018993	,0.010881	,0.00203	,0.000121,
                                        0.000007	,0.000121	,0.000649	,0.001133	,0.000649	,0.000121	,0.000007    );

    /////// 9x9 //////////
    const int largeurTab = 9;
    const int tailleTab = largeurTab * largeurTab;
    float tableau[ tailleTab ]=float[]( 0.	        ,0.	        ,0.000002	,0.000012	,0.000021	,0.000012	,0.000002	,0.	        ,0.  ,
                                        0.	        ,0.000007	,0.000121	,0.000649	,0.001132	,0.000649	,0.000121	,0.000007	,0.,
                                        0.000002	,0.000121	,0.00203	,0.010879	,0.01899	,0.010879	,0.00203	,0.000121	,0.000002,
                                        0.000012	,0.000649	,0.010879	,0.058306	,0.101775	,0.058306	,0.010879	,0.000649	,0.000012,
                                        0.000021	,0.001132	,0.01899	,0.101775	,0.17765	,0.101775	,0.01899	,0.001132	,0.000021,
                                        0.000012	,0.000649	,0.010879	,0.058306	,0.101775	,0.058306	,0.010879	,0.000649	,0.000012,
                                        0.000002	,0.000121	,0.00203	,0.010879	,0.01899	,0.010879	,0.00203	,0.000121	,0.000002,
                                        0.	        ,0.000007	,0.000121	,0.000649	,0.001132	,0.000649	,0.000121	,0.000007	,0.,
                                        0.	        ,0.	        ,0.000002	,0.000012	,0.000021	,0.000012	,0.000002	,0.	        ,0.    );


*/

    vec4 pixel;
    int i = 0;

    for ( int x = 0; x<largeurTab; x++ ){
        for ( int y = 0; y<largeurTab; y++ ){
            int decalX = -( largeurTab - 1) /2  + x;
            int decalY = -( largeurTab - 1) /2  +y;
            pixel += texture2D(texture, gl_TexCoord[0].xy + decalX*offx + decalY*offy) * tableau[i] ;
            i++;

        }
    }

    gl_FragColor =  gl_Color  * pixel ;

}

    // https://software.intel.com/en-us/blogs/2014/07/15/an-investigation-of-fast-real-time-gpu-based-image-blur-algorithms
    // 7x7 convolution kernel with Gauss distribution values
   /* vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)               * .172 +

                 texture2D(texture, gl_TexCoord[0].xy - offx)        * .109 +
                 texture2D(texture, gl_TexCoord[0].xy + offx)        * .109 +
                 texture2D(texture, gl_TexCoord[0].xy - offy)        * .109 +
                 texture2D(texture, gl_TexCoord[0].xy + offy)        * .109 +

                 texture2D(texture, gl_TexCoord[0].xy - offx - offy) * .068 +
                 texture2D(texture, gl_TexCoord[0].xy + offx - offy) * .068 +
                 texture2D(texture, gl_TexCoord[0].xy - offy + offy) * .068 +
                 texture2D(texture, gl_TexCoord[0].xy + offy + offy) * .068 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offx ) * .02 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offx ) * .02 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offy ) * .02 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy ) * .02 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offx - offy) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offx - offy) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offx + offy) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offx + offy) * .012 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offy - offx) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy - offx) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offy + offx) * .012 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy + offx) * .012 +

                 texture2D(texture, gl_TexCoord[0].xy - 2*offy - 2*offx) * .002 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy - 2*offx) * .002 +
                 texture2D(texture, gl_TexCoord[0].xy - 2*offy + 2*offx) * .002 +
                 texture2D(texture, gl_TexCoord[0].xy + 2*offy + 2*offx) * .002 +

                 texture2D(texture, gl_TexCoord[0].xy - 3*offx ) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offx ) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy - 3*offy ) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offy ) * .001 +

                 texture2D(texture, gl_TexCoord[0].xy - 3*offx - offy) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offx - offy) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy - 3*offx + offy) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offx + offy) * .001 +

                 texture2D(texture, gl_TexCoord[0].xy - 3*offy - offx) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offy - offx) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy - 3*offy + offx) * .001 +
                 texture2D(texture, gl_TexCoord[0].xy + 3*offy + offx) * .001 ;

//
}

/*

0	0	0.000002	0.000012	0.000021	0.000012	0.000002	0	0
0	0.000007	0.000121	0.000649	0.001132	0.000649	0.000121	0.000007	0
0.000002	0.000121	0.00203	0.010879	0.01899	0.010879	0.00203	0.000121	0.000002
0.000012	0.000649	0.010879	0.058306	0.101775	0.058306	0.010879	0.000649	0.000012
0.000021	0.001132	0.01899	0.101775	0.17765	0.101775	0.01899	0.001132	0.000021
0.000012	0.000649	0.010879	0.058306	0.101775	0.058306	0.010879	0.000649	0.000012
0.000002	0.000121	0.00203	0.010879	0.01899	0.010879	0.00203	0.000121	0.000002
0	0.000007	0.000121	0.000649	0.001132	0.000649	0.000121	0.000007	0
0	0	0.000002	0.000012	0.000021	0.000012	0.000002	0	0
*/
