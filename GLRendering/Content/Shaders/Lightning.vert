#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 LightingColor; // Resulting color from lighting calculations

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{	
	gl_Position = projection * view * model * vec4(position, 1.0f);
    
    // Gouraud Shading
    // ------------------------
    vec3 Position = vec3(view * model * vec4(position, 1.0f));
    vec3 Normal = mat3(transpose(inverse(view * model))) * normal;
    
    // Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
	vec3 _LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
    vec3 lightDir = normalize(_LightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular
    float specularStrength = 1.0f; // This is set higher to better show the effect of Gouraud shading 
    vec3 viewDir = normalize(-Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;      

    LightingColor = ambient + diffuse + specular;
}