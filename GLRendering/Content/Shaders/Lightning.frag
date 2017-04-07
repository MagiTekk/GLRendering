#version 330 core
out vec4 color;

in vec3 Normal;
in vec3 FragPos;

float ambientStrength = 0.1f;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	// Direction vector between the light source and the fragment's position
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	
	// dot product to get the angle between the normal and the direction vector to get the angle
	// the light has on this fragment
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 ambient = ambientStrength * lightColor;
	vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);
}