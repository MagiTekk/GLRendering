#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	
	// get the fragment position in world coordinates, we have to multiply it with the model matrix - added the view to convert to view position
	FragPos = vec3(view * model * vec4(position, 1.0f));
	LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position
	
	// this here is to obtain the Normal vector in world coordinates
	// but since we cannot just use the model matrix for this
	// we have to calculate the normal matrix by using
	// the transpose of the inverse of the upper-left corner of the model matrix
	// Note that we also cast the matrix to a 3x3 matrix to ensure it loses its translation properties and that it can multiply with the vec3 normal vector
	
	// calculating the normal matrix in world space
	//Normal = mat3(transpose(inverse(model))) * normal;
	
	// this here below was just fine because we did not perform any scaling operation on the object itself 
	// so there was not really a need to use a normal matrix and could've just multiplied the normals with the model matrix
	// Normal = normal;
	
	// calculating the normal matrix in view space
	Normal = mat3(transpose(inverse(model))) * normal;
}