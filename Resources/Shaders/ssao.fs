#version 330 core
layout(location = 0) out vec4 FragColor;

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D noiseTex;

in vec2 TexCoords;

uniform vec3 samples[64];
uniform vec2 screenSize;
uniform mat4 projection;

int kernelSize = 64;
float radius = 0.5;
float bias = 0.025;

void main(void)
{
	// ssao inputs
	vec2 noiseScale = screenSize/vec2(4.0);
	vec3 normal = texture(gNormal, TexCoords).xyz;
	vec3 fragPos = normalize(texture(gPosition, TexCoords).xyz);
	vec3 randomVec = normalize(texture(noiseTex, TexCoords * noiseScale).xyz);
	
	//TBN
	vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 TBN = mat3(tangent,bitangent,normal);
	
	float occlusion = 0.0;
	for(int i = 0; i<kernelSize; ++i)
	{
		// get the sample
		vec3 sample = TBN * samples[i];
		sample = fragPos +sample*radius;
		
		// project sample
		vec4 offset = vec4(sample,1.0);
		offset = projection * offset;
		offset.xyz /= offset.w;
		offset.xyz = offset.xyz * 0.5 + 0.5; //range 0 - 1
		
		// sample depth
		float sampleDepth = texture(gPosition,offset.xy).z;
		
		//range check
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
		occlusion += (sampleDepth >= sample.z + bias ? 1.0 : 0.0) * rangeCheck;
	}
	occlusion = 1.0 - (occlusion / kernelSize);
	
	FragColor = vec4(occlusion,occlusion,occlusion,1.0);
}