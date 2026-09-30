#include "TexturedQuad.h"



TexturedQuad::TexturedQuad(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	initBuffers(device);
}


TexturedQuad::~TexturedQuad()
{
	// Run parent deconstructor
	BaseMesh::~BaseMesh();
}

// Build shape and fill buffers.
void TexturedQuad::initBuffers(ID3D11Device* device)
{
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	vertexCount = 9;
	indexCount = 24;

	VertexType_Texture* vertices = new VertexType_Texture[vertexCount];
	unsigned long* indices = new unsigned long[indexCount];

	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-2.0f, 2.0f, 0.0f);  // Top left.
	vertices[0].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(-2.0f, -2.0f, 0.0f);  // bottom left.
	vertices[1].texture = XMFLOAT2(0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(2.0f, -2.0f, 0.0f);  // bottom right.
	vertices[2].texture = XMFLOAT2(1.0f, 1.0f);

	vertices[3].position = XMFLOAT3(2.0f, 2.0f, 0.0f);  // top right.
	vertices[3].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[4].position = XMFLOAT3(6.0f, 2.0f, 0.0f);  // top right right.
	vertices[4].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[5].position = XMFLOAT3(6.0f, -2.0f, 0.0f);  // bottom right right.
	vertices[5].texture = XMFLOAT2(0.0f, 1.0f);

	vertices[6].position = XMFLOAT3(-6.0f, -6.0f, 0.0f);  // bottom bottom left.
	vertices[6].texture = XMFLOAT2(0.0f, 0.0f);

	vertices[7].position = XMFLOAT3(2.0f, -6.0f, 0.0f);  // bottom bottom right.
	vertices[7].texture = XMFLOAT2(1.0f, 0.0f);

	vertices[8].position = XMFLOAT3(4.0f, -6.0f, 0.0f);  // bottom bottom right right.
	vertices[8].texture = XMFLOAT2(0.0f, 0.0f);
		
	//034
	//125
	//678
		
	// Load the index array with data.
	//top left
	indices[0] = 0;  // Top left
	indices[1] = 1;  // Bottom left.
	indices[2] = 2;  // Bottom right.
	indices[3] = 0;  // Top left.
	indices[4] = 2;  // Bottom right.
	indices[5] = 3;  // Top right.
	//top right
	indices[6] = 3;  // Top left
	indices[7] = 2;  // Bottom left.
	indices[8] = 5;  // Bottom right.
	indices[9] = 3;  // Top left.
	indices[10] = 5;  // Bottom right.
	indices[11] = 4;  // Top right.
	/*
	//bottom left
	indices[12] = 1;  // Top left
	indices[13] = 6;  // Bottom left.
	indices[14] = 7;  // Bottom right.
	indices[15] = 1;  // Top left.
	indices[16] = 7;  // Bottom right.
	indices[17] = 2;  // Top right.
	//bottom right
	indices[18] = 2;  // Top left
	indices[19] = 7;  // Bottom left.
	indices[20] = 8;  // Bottom right.
	indices[21] = 2;  // Top left.
	indices[22] = 8;  // Bottom right.
	indices[23] = 5;  // Top right.
	*/

	D3D11_BUFFER_DESC vertexBufferDesc = { sizeof(VertexType_Texture) * vertexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	vertexData = { vertices, 0 , 0 };
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc = { sizeof(unsigned long) * indexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
	indexData = { indices, 0, 0 };
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
}

// Send Geometry data to the GPU
void TexturedQuad::sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType_Texture);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(top);
}

