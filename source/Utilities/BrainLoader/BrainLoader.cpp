#include <Utilities/BrainLoader/BrainLoader.h>
#include <stdio.h>
#include <nifti/include/nifti1.h>
#include <nifti/include/nifti1_io.h>
#include <Utilities/Debug/Debug.h>

namespace Atum
{
	namespace Utilities
	{
		namespace BrainLoader
		{

			void CreateBrainGeometry(const char * niftiBrainPath, const float & width, const float & height, 
				const float & depth, const int & skipFactor, LowLevelGraphics::GeometryParameters & geomParam)
			{
				ATUM_ASSERT_MESSAGE(width > 0.0f, "The width must be greater than zero");
				ATUM_ASSERT_MESSAGE(height > 0.0f, "The height must be greater than zero");
				ATUM_ASSERT_MESSAGE(depth > 0.0f, "The depth must be greater than zero");
				ATUM_ASSERT_MESSAGE(skipFactor >= 1, "The skip factor must be greater or equal to one");
				if ((width <= 0.0f) || (height <= 0.0f) || (depth <= 0.0f) || (skipFactor < 1))
					return;

				Image3D imageBrain;
				LoadNiftiBrain(niftiBrainPath, imageBrain);
				GenerateCloudPoints(imageBrain, width, height, depth, skipFactor, geomParam.position, geomParam.color);
			}

			enum DatasetType 
			{
				BOT_INITIALIZED = 0,

				// Textures
				HEAD_BYTE,
				HEAD_SHORT,
				OVERLAY,
				RGB,
				TENSOR_FIELD,

				// Everything higher can't be used as a texture.
				MESH,
				VECTORS,
				TENSORS,
				ODFS,
				MAXIMAS,
				FIBERS,
				SURFACE,
				ISO_SURFACE,
				MASTER_OBJECT,
				CHILD_OBJECT,
				LABEL_POINTS,
				LABEL_SELECTION_OBJECTS,
				NOT_INITIALIZED,
				FIBERSGROUP
			};

			// This code was taken from the fiber navigator project
			bool LoadNiftiBrain(const char * niftiBrainPath, Image3D & brainImage3D)
			{
				FILE * file;
				if(fopen_s(&file, niftiBrainPath, "r") != 0)
				{
					printf("Impossible to open the object file !\n");
					return false;
				}

				nifti_image * header = nifti_image_read(niftiBrainPath, 0);
				nifti_image * body   = nifti_image_read(niftiBrainPath, 1);

				int columns   = header->dim[1];
				int rows      = header->dim[2];
				int frames    = header->dim[3];
				int bands     = header->dim[4];
				int dataType  = header->datatype;

				// Fix the case where some nifti files have a value of 0 for the fourth
				// dimension. It is a valid case, but some of the code use the number of bands
				// to process the data indenpendantly from its dimension.
				if( bands == 0 )
				{
					bands = 1;
				}

				int voxelSizeX = header->dx;
				int voxelSizeY = header->dy;
				int voxelSizeZ = header->dz;

				int type;
				// Check the data type.
				if (dataType == 2)
				{
					if (header->dim[4] == 1)
					{
						type = HEAD_BYTE;
					}
					else if (header->dim[4] == 3)
					{
						type = RGB;
					}
					else
					{
						type = BOT_INITIALIZED;
					}
				}
				else if (dataType == 4)
				{
					type = HEAD_SHORT;
				}
				else if (dataType == 16)
				{
					if (header->dim[4] == 3)
					{
						type = VECTORS;
					}
					else
					{
						type = OVERLAY;
					}
				}
				else
				{
					type = BOT_INITIALIZED;
				}

				int brainSize = columns * rows * frames;

				bool isLoaded = false;
				std::vector<float> brainFloatValues;
				int oldMax;
				int newMax;

				switch(type)
				{
				case HEAD_BYTE:
					{
						unsigned char* data = (unsigned char*)body->data;
						brainFloatValues.resize(brainSize);

						for ( int i(0); i < brainSize; ++i)
						{
							brainFloatValues[i] = (float)data[i] / 255.0;
						}

						isLoaded = true;
						oldMax = 255;
						break;
					}
				case HEAD_SHORT:
					{
						short int* data = (short int*)body->data;
						int dataMax = 0;
						std::vector<int> histo(65536, 0);

						for (int i = 0; i < brainSize; ++i)
						{
							dataMax = max(dataMax, (int)data[i]);
							++histo[data[i]];
						}

						int nbElements   = (int)(brainSize * 0.001);
						int newMax       = 65535;
						int adder         = 0;
						for (int i = 65535; i > 0; --i)
						{
							adder += histo[i];
							newMax = i;
							if(adder > nbElements)
							{
								break;
							}
						}

						for (int i = 0; i < brainSize; ++i)
						{
							if ( data[i] > newMax )
							{
								data[i] = newMax;
							}
						}

						brainFloatValues.resize(brainSize);

						for (int i(0); i < brainSize; ++i)
						{
							brainFloatValues[i] = (float)data[i] / (float)newMax;
						}

						oldMax = dataMax;
						isLoaded = true;
						break;
					}
				case OVERLAY:
					{
						float* data = (float*)body->data;

						brainFloatValues.resize(brainSize);

						for( int i = 0; i < brainSize; ++i )
						{
							brainFloatValues[i] = (float)data[i];
						}

						float dataMax = 0.0f;
						for (int i = 0; i < brainSize; ++i)
						{
							if (brainFloatValues[i] > dataMax)
							{
								dataMax = brainFloatValues[i];
							}
						}

						for (int i(0); i < brainSize; ++i)
						{
							brainFloatValues[i] = brainFloatValues[i] / dataMax;
						}

						oldMax    = dataMax;
						newMax    = 1.0;
						isLoaded = true;
						break;
					}
				case RGB:
					{
						unsigned char* data = (unsigned char*)body->data;

						brainFloatValues.resize(brainSize * 3);
						for( int i = 0; i < brainSize; ++i )
						{
							brainFloatValues[i * 3]       = (float)data[i]  / 255.0f;
							brainFloatValues[i * 3 + 1]   = (float)data[brainSize + i] / 255.0f;
							brainFloatValues[i * 3 + 2]   = (float)data[(2 * brainSize) + i] / 255.0f;
						}

						isLoaded = true;
						break;
					}
				case VECTORS:
					{
						float* data = (float*)body->data;

						brainFloatValues.resize(brainSize * 3);
						for (int i = 0; i < brainSize; ++i)
						{
							brainFloatValues[i * 3] = data[i];
							brainFloatValues[i * 3 + 1] = data[brainSize + i];
							brainFloatValues[i * 3 + 2] = data[2 * brainSize + i];
						}

						isLoaded = true;
						break;
					}

				default:
					{
						//Logger::getInstance()->print( wxT( "Unsupported file format" ), LOGLEVEL_ERROR );
						isLoaded = false;
						// Will not return now to make sure the pHdrFile pointer is freed.
					}
				}

				if (isLoaded)
				{
					brainImage3D = Image3D(brainFloatValues, columns, rows, frames);
				}

				return isLoaded;
			}

			void GenerateCloudPoints(const Image3D & image3D, const float & realWidth, const float & realHeight, 
				const float & realDepth, const unsigned int & skipFactor, vector<glm::vec3> & vertices, 
				vector<glm::vec4> & colors)
			{
				ATUM_ASSERT_MESSAGE(realWidth > 0.0f, "The width must be greater than zero");
				ATUM_ASSERT_MESSAGE(realHeight > 0.0f, "The height must be greater than zero");
				ATUM_ASSERT_MESSAGE(realDepth > 0.0f, "The depth must be greater than zero");
				ATUM_ASSERT_MESSAGE(skipFactor >= 1, "The skip factor must be greater or equal to one");
				if ((realWidth <= 0.0f) || (realHeight <= 0.0f) || (realDepth <= 0.0f) || (skipFactor < 1))
					return;

				unsigned int width = image3D.GetNbColumns();
				unsigned int height = image3D.GetNbRows();
				unsigned int depth = image3D.GetNbFrames();
				float dx = (realWidth/width)*skipFactor;
				float dz = (realHeight/height)*skipFactor;
				float dy = (realDepth/depth)*skipFactor;

				glm::vec3 vertex;
				float alphaValue;

				vertex.y = -realDepth/2;
				for (unsigned int k = 0; k < depth; k+=skipFactor)
				{
					vertex.z = -realHeight/2;
					for (unsigned int j = 0; j < height; j+=skipFactor)
					{
						vertex.x = -realWidth/2;
						for (unsigned int i = 0; i < width; i+=skipFactor)
						{
							alphaValue = image3D.GetValue(i,j,k);
							if (alphaValue > 0.2f)
							{
								vertices.push_back(vertex);
								colors.push_back(glm::vec4(alphaValue,alphaValue,alphaValue,alphaValue));
							}

							vertex.x += dx;
						}

						vertex.z += dz;
					}

					vertex.y += dy;
				}
			}

		}
	}

}