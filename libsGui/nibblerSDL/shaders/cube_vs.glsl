#version 410 core

#define NB_BLOCK_TYPES 4

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aSize;
layout (location = 2) in float aFaceId;

out GS_IN {
	flat int FaceId;
	vec2 FSize;
	vec3 Normal;
	flat int TextureId;
} vs_out;

uniform int[NB_BLOCK_TYPES * 6] blockTextures;
uniform sampler2DArray	textureAtlas;

uniform int blockId = 0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 normals[6] = vec3[6](
	vec3(0.0f, 0.0f, 1.0f),
	vec3(1.0f, 0.0f, 0.0f),
	vec3(0.0f, 0.0f, -1.0f),
	vec3(-1.0f, 0.0f, 0.0f),
	vec3(0.0f, 1.0f, 0.0f),
	vec3(0.0f, -1.0f, 0.0f)
);

void main() {
	vs_out.FaceId = int(aFaceId);
	vs_out.FSize = aSize;
	vs_out.Normal = mat3(transpose(inverse(model))) * normals[int(aFaceId)];

	// retrieve texture id
	vs_out.TextureId = blockTextures[blockId * 6 + int(aFaceId)];

	gl_Position = vec4(aPos, 1.0);
}
