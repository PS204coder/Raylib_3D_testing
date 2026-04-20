#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragPosition;
in vec3 fragNormal;
// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;
uniform vec3 viewPos;


// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);

    // NOTE: Implement here your fragment shader code

    // final color is the color from the texture
    //    times the tint color (colDiffuse)
    //    times the fragment color (interpolated vertex color)
    //finalColor = texelColor*colDiffuse*fragColor;
    //finalColor = vec4(mod(fragPosition * 10, 1.0), 1.0);
    
        

    vec3 light_ball_pos_1 = vec3(20.0,0.0,-15.0);
    vec3 light_ball_pos_2 = vec3(-20.0,0.0,-15.0);
    vec3 light1 = light_ball_pos_1 - fragPosition;
    vec3 light2 = light_ball_pos_2 - fragPosition;
    float light1_lenght = length(light1) /10;
    float light2_lenght = length(light2) /10;
    if (light1_lenght > 0){
        light1_lenght = 1/light1_lenght;
    }
    if (light2_lenght>0){
        light2_lenght = 1/light2_lenght;
    }
    
    float diff1 = max(dot(fragNormal, light1), 0.0);
    float diff2 = max(dot(fragNormal, light2), 0.0);
    
    vec3 diffuse = (diff1+diff2)* texelColor.xyz;
    
    //specular lighting stuff
    vec3 reflectdir = reflect(-light1, fragNormal);
    vec3 viewdir = normalize(viewPos-fragPosition);
    
    float spec = pow(max(dot(viewdir, reflectdir), 0.0), 32);
    
    vec3 color = vec3(0.6, 0.6, 0.6);
    color += vec3(0.0, max(dot(normalize(light1), normalize(fragNormal)) * light1_lenght, 0.0), 0.0);
    color += vec3(0.0, 0.0,max(dot(normalize(light2), normalize(fragNormal)) * light2_lenght,0.0));
    color *= texelColor.xyz;

    
    
    finalColor = vec4(color, 1);
}
    