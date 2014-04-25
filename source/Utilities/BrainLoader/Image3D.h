#ifndef UTILITIES_IMAGE3D_H
#define UTILITIES_IMAGE3D_H

#include <vector>
#include <GLM/include/glm/glm.hpp>
using namespace std;

namespace Atum
{
	namespace Utilities
	{
		namespace BrainLoader
		{
			const float INFINITY = 100000.0f;
			const float EPSILON = 0.0001f;

			class Image3D
			{
			public:
				Image3D();
				Image3D(const vector<float> & dataValues, const unsigned int & nbColumns, const unsigned int & nbRows, const unsigned int & nbFrames);

				float GetValue(const unsigned int & column, const unsigned int & row, const unsigned int & frame)
				{
					return m_data[column + row * m_nbColumns + frame * m_nbColumns * m_nbRows];
				}

				const float GetValue(const unsigned int & column, const unsigned int & row, const unsigned int & frame) const
				{
					return m_data[column + row * m_nbColumns + frame * m_nbColumns * m_nbRows];
				}

				void SetValue(const unsigned int & column, const unsigned int & row, const unsigned int & frame, const float & value)
				{
					m_data[column + row * m_nbColumns + frame * m_nbColumns * m_nbRows] = value;
				}

				const float * GetData() const { return &m_data[0]; }

				float * GetData() { return &m_data[0]; }

				const float * GetFrame(const int & frame) const { return &m_data[frame * m_nbColumns * m_nbRows]; }

				float * GetFrame(const int & frame) { return &m_data[frame * m_nbColumns * m_nbRows]; }

				float GetFrameMaxValue(const int & frame);

				void Segmente(float threshold);

				vector<vector<glm::vec3>> GenerateSurface();

				// Apply a blur filter convolution here and a threshold filter
				void RemoveNoise();

				// Apply a high frequency gaussian filter
				void EnhanceEdges();

				// Segmentation of the 3d image with a k-mean
				void KMeans();

				unsigned int GetNbColumns() const { return m_nbColumns; }
				unsigned int GetNbRows() const { return m_nbRows; }
				unsigned int GetNbFrames() const { return m_nbFrames; }
				unsigned int GetDataSize() const { return m_dataSize; }

				// This code for saving the series of bmp was taken from our tp of visual interaction
				void SaveBmp(const char * path);

			private:

				vector<float> m_data;
				unsigned int m_nbColumns;
				unsigned int m_nbRows;
				unsigned int m_nbFrames;
				unsigned int m_dataSize;
			};
		}
	}
}

#endif

