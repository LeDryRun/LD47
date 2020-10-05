//
// Shader that only shows part of sprite based on ratio
// Radially based, 100%
//
uniform sampler2D BaseTexture;
uniform float percentage;

void main(void)
{
	vec2 full  = vec2(0.0f, 0.5f);
	vec2 empty = vec2(0.5f, 1.0f);

    vec4 Color;
    Color += texture(BaseTexture, gl_TexCoord[0].xy).rgba;
    gl_FragColor =  Color *  gl_Color;
}