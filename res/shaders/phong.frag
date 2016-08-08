#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct BaseLight
{
	vec3 color;
	float ambient;
};

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct DirLight
{
	BaseLight base;
	vec3 direction;
};

struct PointLight
{
	BaseLight base;
	vec3 position;
	Attenuation atten;
};

struct SpotLight
{
	BaseLight base;
	vec3 position;
	vec3 direction;
	float innerCutoff;
	float outerCutoff;
	Attenuation atten;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
#define POINT_LIGHT_AMOUNT 4
uniform PointLight pointLights[POINT_LIGHT_AMOUNT];
uniform SpotLight spotLight;

vec3 calcLight(BaseLight base, vec3 lightDir, vec3 viewDir, vec3 norm, vec3 diffuseColor, vec3 specularAmount)
{
	float diffuseFactor = max(dot(norm, lightDir), 0.0f);
	float specularFactor = pow(max(dot(viewDir, reflect(-lightDir, norm)), 0.0f), material.shininess);
	vec3 ambient = base.ambient * diffuseColor;
	vec3 diffuse = base.color * diffuseFactor * diffuseColor;
	vec3 specular = base.color * specularFactor * specularAmount;
	return ambient + diffuse + specular;
}

vec3 calcDirLight(DirLight light, vec3 viewDir, vec3 norm, vec3 diffuseColor, vec3 specularAmount)
{
	return calcLight(light.base, normalize(-light.direction), viewDir, norm, diffuseColor, specularAmount);
}

vec3 calcPointLight(PointLight light, vec3 viewDir, vec3 fragPos, vec3 norm, vec3 diffuseColor, vec3 specularAmount)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 color = calcLight(light.base, lightDir, viewDir, norm, diffuseColor, specularAmount);
	float dist = length(light.position - fragPos);
	float atten = 1.0f / (light.atten.constant + 
						  light.atten.linear * dist + 
						  light.atten.quadratic * dist * dist);

	return color * atten;
}

vec3 calcSpotLight(SpotLight light, vec3 viewDir, vec3 fragPos, vec3 norm, vec3 diffuseColor, vec3 specularAmount)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.innerCutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0f, 1.0f);
	vec3 color = calcLight(light.base, lightDir, viewDir, norm, diffuseColor, specularAmount);
	float dist = length(light.position - fragPos);
	float atten = 1.0f / (light.atten.constant + 
						  light.atten.linear * dist + 
						  light.atten.quadratic * dist * dist);
	return color * atten * intensity;

}

void main()
{
	vec3 diffuse = vec3(texture(material.diffuse, TexCoords));
	vec3 specular = vec3(texture(material.specular, TexCoords));
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 res = calcDirLight(dirLight, viewDir, norm, diffuse, specular);
	for (int i = 0; i < POINT_LIGHT_AMOUNT; i++)
	{
		res += calcPointLight(pointLights[i], viewDir, FragPos, norm, diffuse, specular);
	}
	res += calcSpotLight(spotLight, viewDir, FragPos, norm, diffuse, specular);
	color = vec4(res, 1.0f);
}