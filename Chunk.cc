#include "Chunk.hh"

#include <iostream>


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Chunk Implementation
/////////////////////////////////////////////////////////////////////////////////////////////////////

Chunk::Chunk(const glm::ivec3& p_gridOrigin)
  : m_gridCoordinates{p_gridOrigin},
    m_origin{p_gridOrigin.x, p_gridOrigin.y, p_gridOrigin.z},
    m_needsMeshUpdate{true} {

  m_origin *= CHUNK_SIZE;
  Update();
}

void Chunk::Update() {

  if (m_needsMeshUpdate)
    ExtractMesh();
}

void Chunk::Render() {

  m_mesh.Render();
}

void Chunk::ExtractMesh() {

  for (std::size_t i = 0; i < CHUNK_SIZE; ++i)
    for (std::size_t j = 0; j < CHUNK_SIZE; ++j)
      for (std::size_t k = 0; k < CHUNK_SIZE; ++k) {
        m_blocks[i][j][k] = 1;
        m_mesh.AddCube({m_origin.x + i, m_origin.y + j, m_origin.z + k}, BLOCK_WIDTH);
      }
  m_mesh.BufferData();
  m_needsMeshUpdate = false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
