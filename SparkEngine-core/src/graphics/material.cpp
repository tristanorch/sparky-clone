#include "material.h"
#include "texture.h"
namespace sparky { namespace graphics {
	
	Material::Material()
	{
		addTexture("diffuse", &Texture(defaultDiffuse));
		addTexture("normalMap", &Texture(defaultNormal));
		addTexture("dispMap", &Texture(defaultDisp));
		addFloat("specularIntensity", 1.0f);
		addFloat("specularPower", 0.01f);
		addFloat("dispMapScale", 0.0f);
		addFloat("dispMapBias", 0.0f);
	}

	Material::Material(Texture* diffuse, float specularIntensity, float specularPower, Texture* normalMap, Texture* dispMap, float dispMapScale, float dispMapOffset) : Material()
	{
		if (diffuse != nullptr) addTexture("diffuse", diffuse);
		if (normalMap != nullptr) addTexture("normalMap", normalMap);
		if (dispMap != nullptr) addTexture("dispMap", dispMap);
		if (specularIntensity != 0) addFloat("specularIntensity", specularIntensity);
		if (specularPower != 0) addFloat("specularPower", specularPower);
		if (dispMapScale != 0) addFloat("dispMapScale", dispMapScale);
		float baseBias = dispMapScale / 2.0f;
		if (dispMapOffset != 0) addFloat("dispMapBias", -baseBias + baseBias * dispMapOffset);
	}

	void Material::useDefaultNormal()
	{
		addTexture("normalMap", &Texture(defaultNormal));
	}

	void Material::addTexture(const std::string & name, Texture * texture)
	{
		textureHashMap[name] = texture;
	}

	Texture* Material::getTexture(std::string name)
	{
		Texture* resource;
		auto result = textureHashMap.find(name);
		if (result != textureHashMap.end()) {
			resource = result->second;
		}
		else {
			std::cout << "Error: [TEXTURE] unable to retrieve <" << name.c_str() << "> from texture HashMap." << std::endl;
			exit(1);
		}
		return resource;
	}

	Material* Material::DebugMaterial()
	{
		this->addTexture("diffuse", &Texture(defaultDiffuse));
		this->addFloat("specularIntensity", 1.0f);
		this->addFloat("specularPower", 0.01f);
		return this;
	}


} }