#ifndef MODEL_BUILDER_HPP
#define MODEL_BUILDER_HPP

#include <vector>
#include "../VertexStream/VertexStream.h"
#include <glad/glad.h>
#include "Mesh.h"

using namespace std;

namespace EngineRender::Mesh
{
    
template<typename T> class ModelBuilder : public Mesh
{
public:
	ModelBuilder(int allocateVertexes, VertexStream::VertexStream* stream) :
		_vertexArray(std::make_unique<vector<T>>()),
		_indexArray(std::make_unique<vector<unsigned int>>()),
		_stream(stream),
		_instances(std::make_unique<vector<glm::mat4>>())
	{
		_vertexArray->reserve(allocateVertexes);
		_indexArray->reserve(allocateVertexes);
	}

	void AddTriangle(const T& v1, const T& v2, const T& v3)
	{
		_vertexArray->push_back(v1);
		_vertexArray->push_back(v2);
		_vertexArray->push_back(v3);

		const unsigned int size = _indexArray->size();
		_indexArray->push_back(size);
		_indexArray->push_back(size + 1);
		_indexArray->push_back(size + 2);
	}

	void AddQuad(const T& v1, const T& v2, const T& v3, const T& v4) {
		const unsigned int size = static_cast<unsigned int>(_vertexArray->size());

		_vertexArray->push_back(v1);
		_vertexArray->push_back(v2);
		_vertexArray->push_back(v3);
		_vertexArray->push_back(v4);

		
		_indexArray->push_back(size);
		_indexArray->push_back(size + 1);
		_indexArray->push_back(size + 2);

		_indexArray->push_back(size);
		_indexArray->push_back(size + 2);
		_indexArray->push_back(size + 3);
	}
	
	void SubmitModel()
	{
		glGenVertexArrays(1, &_VAO);
		glGenBuffers(1, &_VBO);
		glGenBuffers(1, &_EBO);

		glBindVertexArray(_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);

		glBufferData(GL_ARRAY_BUFFER, _stream->GetSize() * _vertexArray->size(), _vertexArray->data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * _indexArray->size(), _indexArray->data(), GL_STATIC_DRAW);

		_stream->InitAttributePointers();
		_modelSize = _indexArray->size();
	}

	void AddInstance(const glm::mat4& transform)
	{
		_instances->push_back(transform);
	}

	const std::unique_ptr<vector<glm::mat4>>& GetInstances() const
	{
		return _instances;
	}

	void Attach() const override { glBindVertexArray(_VAO); }
	unsigned int GetDrawSize() const override { return _modelSize; }

private:
	std::unique_ptr<vector<T>> _vertexArray;
	std::unique_ptr<vector<unsigned int>> _indexArray;
	unsigned int _modelSize;

	unsigned int _VAO;
	unsigned int _VBO;
	unsigned int _EBO;

	std::unique_ptr<VertexStream::VertexStream> _stream;
	std::unique_ptr<vector<glm::mat4>> _instances;
};

}

#endif