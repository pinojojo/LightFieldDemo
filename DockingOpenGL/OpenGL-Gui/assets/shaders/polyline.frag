#version 330 core
uniform bool is_hole;

out vec4 FragColor;
void main()
{
	vec4 result=vec4(1.0,0.0,0.0,1.0);

	if(is_hole)
	{	
		result=vec4(0.0,1.0,0.0,1.0);
	}


	FragColor = result;
}