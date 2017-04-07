#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;

float ambientStrength = 0.1f;
float specularStrength = 0.5f;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{
	// Direction vector between the light source and the fragment's position
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	// calculating the specular lighting
	// This 32 value is the shininess value of the highlight. The higher the shininess value of an object, the more it properly reflects
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	// dot product to get the angle between the normal and the direction vector to get the angle
	// the light has on this fragment
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);
}