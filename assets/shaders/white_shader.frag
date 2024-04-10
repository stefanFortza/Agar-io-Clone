uniform sampler2D texture;
uniform float time;

void main()
{
    // Get the pixel color from the texture
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    // Calculate grayscale value
    float grayscale = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));

    // Add outline
    float outline = fwidth(grayscale);

    // Apply a hit effect based on time
    float hitEffect = 1.0 - smoothstep(0.0, 0.5, time);

    // Blend original color with grayscale and outline
    vec4 finalColor = mix(color, vec4(grayscale, grayscale, grayscale, 1.0), hitEffect);
    finalColor = mix(finalColor, vec4(1.0), outline);

    gl_FragColor = finalColor;
}