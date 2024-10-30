#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform float ShininessStrength ;


void main()
{
   vec3 color = texture(texture1, TexCoord).rgb;
  
    vec3 ambient = ambientStrength * color;
  	
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor * color;
   
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), ShininessStrength);
  
    vec3 specular = vec3(specularStrength) * spec * color *lightColor; 
    FragColor = vec4(ambient + diffuse + specular, 1.0);

} 