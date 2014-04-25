#include <Utilities/BrainLoader/Image3D.h>
#include <stdio.h>
#include <nifti/include/nifti1.h>
#include <nifti/include/nifti1_io.h>

namespace Atum
{
	namespace Utilities
	{
		namespace BrainLoader
		{
			Image3D::Image3D() : m_data(0), m_nbColumns(0), m_nbRows(0), m_nbFrames(0), m_dataSize(0)
			{
			}

			Image3D::Image3D(const vector<float> & dataValues, const unsigned int & nbColumns, const unsigned int & nbRows, const unsigned int & nbFrames)
			{
				m_data = dataValues;
				m_nbColumns = nbColumns;
				m_nbRows = nbRows;
				m_nbFrames = nbFrames;
				m_dataSize = m_nbColumns * m_nbRows * m_nbFrames;
			}

			float Image3D::GetFrameMaxValue(const int & frame)
			{
				float maxValue = -INFINITY;
				for (int j=0;j<m_nbRows;j++)
				{
					for (int i=0;i<m_nbColumns;i++)
					{
						if(GetValue(i,j,frame) > maxValue)
							maxValue = GetValue(i,j,frame);
					}
				}

				return maxValue;
			}

			void Image3D::Segmente(float threshold)
			{
				for(int i = 0; i < m_dataSize; ++i)
				{
					if (m_data[i] > threshold)
						m_data[i] = 1.0f;
					else
						m_data[i] = 0.0f;
				}
			}

			vector<vector<glm::vec3>> Image3D::GenerateSurface()
			{
				vector<vector<glm::vec3>> surface;
				surface.resize(m_nbFrames);
				for (unsigned int frame = 0; frame < m_nbFrames; frame++)
				{
					bool valueFound = false;
					glm::vec3 lastPosFound;
					int firstRowFound=0;
					for (int j=0; j<m_nbRows; ++j)
					{
						for (int i=0; i<m_nbColumns; ++i)
						{
							if (GetValue(i,j,frame) > 0.5f)
							{
								lastPosFound = glm::vec3(i,j,frame);
								surface[frame].push_back(lastPosFound);
								valueFound = true;
								firstRowFound = j;
							}
						}

						if(valueFound)
							break;
					}

					if (!valueFound)
						continue;

					for (int j=lastPosFound.y+1; j<m_nbRows; ++j)
					{
						valueFound = false;
						for (int i=m_nbColumns; i>=0; --i)
						{
							if (GetValue(i,j,frame) > 0.5f)
							{
								lastPosFound = glm::vec3(i,j,frame);
								surface[frame].push_back(lastPosFound);
								valueFound = true;
								break;
							}
						}

						if (!valueFound)
							break;
					}

					for (int j=lastPosFound.y-1; j>firstRowFound; --j)
					{
						for (int i=0; i<m_nbColumns; ++i)
						{
							if (GetValue(i,j,frame) > 0.5f)
							{
								lastPosFound = glm::vec3(i,j,frame);
								surface[frame].push_back(lastPosFound);
								valueFound = true;
								break;
							}
						}
					}
				}

				return surface;
			}

			// Apply a high frequency gaussian filter
			void Image3D::EnhanceEdges()
			{
				//float laplacianFilter[9] = {0.0f,-1.0f,0.0f,-1.0f, 5.0f,-1.0f,0.0f,-1.0f,0.0f};
				float gaussianFilter[25] = {-0.0297f, -0.1331f, -0.2194f, -0.1331f, -0.0297f,
					-0.1331f, -0.5963f, -0.9832f, -0.5963f, -0.1331f,
					-0.2194f, -0.9832f, 8.3790f, -0.9832f, -0.2194f,
					-0.1331f, -0.5963f, -0.9832f, -0.5963f, -0.1331f,
					-0.0297f, -0.1331f, -0.2194f, -0.1331f, -0.0297f};
				int size = m_nbColumns*m_nbRows;
				float * imageTemp = new float[size];
				for (int i = 0; i < size; ++i)
				{
					imageTemp[i] = 0.0f;
				}

				float gaussianValue = 0.0f;

				for (unsigned int frame = 0; frame < m_nbFrames; frame++)
				{
					for (int j=2;j<m_nbRows-2;++j)
					{
						for (int i=2;i<m_nbColumns-2;++i)
						{
							gaussianValue = 0.0f;
							for (int k=0;k<5;++k)
							{
								for (int l=0;l<5;++l)
								{
									gaussianValue += gaussianFilter[k*5+l]*GetValue(i+l-1,j+k-1,frame);
								}
							}

							imageTemp[j*m_nbColumns+i] = gaussianValue;
						}
					}

					for (int j=0;j<m_nbRows;++j)
					{
						for (int i=0;i<m_nbColumns;++i)
						{
							SetValue(i,j,frame,imageTemp[j*m_nbColumns+i]);
						}
					}
				}

				delete [] imageTemp;
			}

			// Apply a blur filter convolution here and a threshold filter
			void Image3D::RemoveNoise()
			{
				//float gaussianFilter[9] = {0.0625f,0.125f,0.0625f,0.125f,0.25f,0.125f,0.0625f,0.125f,0.0625f};
				float gaussianFilter[25] = {0.003663f,0.014652f,0.025641f,0.014652f,0.003663f,
					0.014652f,0.058608f,0.095238f,0.058608f,0.014652f,
					0.025641f,0.095238f,0.150183f,0.095238f,0.025641f,
					0.014652f,0.058608f,0.095238f,0.058608f,0.014652f,
					0.003663f,0.014652f,0.025641f,0.014652f,0.003663f};
				int size = m_nbColumns*m_nbRows;
				float * imageTemp = new float[size];
				for (int i = 0; i < size; ++i)
				{
					imageTemp[i] = 0.0f;
				}

				float gaussianValue = 0.0f;

				for (unsigned int frame = 0; frame < m_nbFrames; frame++)
				{
					for (int j=2;j<m_nbRows-2;++j)
					{
						for (int i=2;i<m_nbColumns-2;++i)
						{
							gaussianValue = 0.0f;
							for (int k=0;k<5;++k)
							{
								for (int l=0;l<5;++l)
								{
									gaussianValue += gaussianFilter[k*5+l]*GetValue(i+l-1,j+k-1,frame);
								}
							}

							imageTemp[j*m_nbColumns+i] = gaussianValue;
						}
					}

					for (int j=0;j<m_nbRows;++j)
					{
						for (int i=0;i<m_nbColumns;++i)
						{
							SetValue(i,j,frame,imageTemp[j*m_nbColumns+i]);
						}
					}
				}

				delete [] imageTemp;

				for(int i = 0; i < m_dataSize; ++i)
				{
					if (m_data[i] < 0.15f)
					{
						m_data[i] = 0.0f;
					}
				}
			}

			// Segmentation of the 3d image with a k-mean
			void Image3D::KMeans()
			{
				int size = m_nbColumns*m_nbRows;
				unsigned char * labelData = new unsigned char[size];
				for (unsigned int frame = 0; frame < m_nbFrames; frame++)
				{
					if (GetFrameMaxValue(frame) < 0.5f)
					{
						// make it black
						for (int j=0;j<m_nbRows;++j)
						{
							for (int i=0;i<m_nbColumns;++i)
							{
								SetValue(i,j,frame,0.0f);
							}
						}
						continue;
					}

					float mu1[2], mu2[2];
					int nbpixelk1;
					int nbpixelk2;

					mu1[1] = 0.2f;
					mu2[1] = 0.8f;

					do{
						mu1[0] = mu1[1];
						mu2[0] = mu2[1];
						nbpixelk1 = nbpixelk2 = 0;
						for (int j=0;j<m_nbRows;++j)
						{
							for (int i=0;i<m_nbColumns;++i)
							{
								if((pow((GetValue(i,j,frame)-mu2[1]),2)) < (pow((GetValue(i,j,frame)-mu1[1]),2)))
								{
									labelData[j * m_nbColumns + i] = 255;
									nbpixelk2++;
								}
								else{
									labelData[j * m_nbColumns + i] = 0;
									nbpixelk1++;
								}
							}
						}

						mu1[1] = mu2[1] = 0.0f;

						for (int j=0;j<m_nbRows;j++)
						{
							for (int i=0;i<m_nbColumns;i++)
							{
								if(labelData[j * m_nbColumns + i] == 255)
									mu2[1] += GetValue(i,j,frame);
								else
									mu1[1] += GetValue(i,j,frame);
							}
						}

						if(nbpixelk1 != 0)
						{
							mu1[1] /= nbpixelk1;
						}

						if(nbpixelk2 != 0)
						{
							mu2[1] /= nbpixelk2;
						}
					}
					while ((mu2[1]<mu2[0]-EPSILON || mu2[1]>mu2[0]+EPSILON) && (mu1[1]<mu1[0]-EPSILON || mu1[1]>mu1[0]+EPSILON));

					for (int j=0;j<m_nbRows;j++)
					{
						for (int i=0;i<m_nbColumns;i++)
						{
							if(labelData[j * m_nbRows + i] == 255)
								SetValue(i,j,frame,1.0f);
							else
								SetValue(i,j,frame,0.0f);
						}
					}
				}

				delete[] labelData;
			}
			// This code for saving a bmp was taken from our tp of visual interaction
			struct BitmapFileHeader
			{
				BitmapFileHeader()
					:   bfType(19778)
					,   bfSize(0)
					,   bfReserved1(0)
					,   bfReserved2(0)
					,   bfOffBits(0)
				{}

				void Read(FILE* pFile)
				{
					fread(&bfType,      sizeof(unsigned short), 1,pFile);
					fread(&bfSize,      sizeof(unsigned int),  1,pFile);
					fread(&bfReserved1, sizeof(unsigned short), 1,pFile);
					fread(&bfReserved2, sizeof(unsigned short), 1,pFile);
					fread(&bfOffBits,   sizeof(unsigned int),  1,pFile);
				}

				void Write(FILE* pFile)
				{
					fwrite(&bfType,     sizeof(unsigned short), 1,pFile);
					fwrite(&bfSize,     sizeof(unsigned int),  1,pFile);
					fwrite(&bfReserved1,sizeof(unsigned short), 1,pFile);
					fwrite(&bfReserved2,sizeof(unsigned short), 1,pFile);
					fwrite(&bfOffBits,  sizeof(unsigned int),  1,pFile);
				}

				unsigned short  bfType;
				unsigned int   bfSize;
				unsigned short  bfReserved1;
				unsigned short  bfReserved2;
				unsigned int   bfOffBits;
			} ;

			// This code for saving a bmp was taken from our tp of visual interaction
			struct BitmapInfoHeader
			{
				BitmapInfoHeader()
					:    biSize(40),biWidth(0),biHeight(0),biPlanes(1),biBitCount(24)
					,    biCompression(0),    biSizeImage(0),    biXPelsPerMeters(0)
					,    biYPelsPerMeters(0), biClrUsed(0),    biClrImportant(0)
				{}

				//Read and Write are implemented independently since
				//the windows' BitmapInfoHeader uses platform specific
				//compiler byte alignement tricks that are hardly portable.

				void Read(FILE* pFile)
				{
					fread(&biSize,          sizeof(unsigned int),  1,pFile);
					fread(&biWidth,         sizeof(int),           1,pFile);
					fread(&biHeight,        sizeof(int),           1,pFile);
					fread(&biPlanes,        sizeof(unsigned short), 1,pFile);
					fread(&biBitCount,      sizeof(unsigned short), 1,pFile);
					fread(&biCompression,   sizeof(unsigned int),  1,pFile);
					fread(&biSizeImage,     sizeof(unsigned int),  1,pFile);
					fread(&biXPelsPerMeters,sizeof(int),           1,pFile);
					fread(&biYPelsPerMeters,sizeof(int),           1,pFile);
					fread(&biClrUsed,       sizeof(unsigned int),  1,pFile);
					fread(&biClrImportant,  sizeof(unsigned int),  1,pFile);
				}

				void Write(FILE* pFile)
				{
					fwrite(&biSize,             sizeof(unsigned int),  1,pFile);
					fwrite(&biWidth,            sizeof(int),           1,pFile);
					fwrite(&biHeight,           sizeof(int),           1,pFile);
					fwrite(&biPlanes,           sizeof(unsigned short), 1,pFile);
					fwrite(&biBitCount,         sizeof(unsigned short), 1,pFile);
					fwrite(&biCompression,      sizeof(unsigned int),  1,pFile);
					fwrite(&biSizeImage,        sizeof(unsigned int),  1,pFile);
					fwrite(&biXPelsPerMeters,   sizeof(int),           1,pFile);
					fwrite(&biYPelsPerMeters,   sizeof(int),           1,pFile);
					fwrite(&biClrUsed,          sizeof(unsigned int),  1,pFile);
					fwrite(&biClrImportant,     sizeof(unsigned int),  1,pFile);
				}

				unsigned int    biSize;
				long            biWidth;
				long            biHeight;
				unsigned short  biPlanes;
				unsigned short  biBitCount;
				unsigned int    biCompression;
				unsigned int    biSizeImage;
				int             biXPelsPerMeters;
				int             biYPelsPerMeters;
				unsigned int    biClrUsed;
				unsigned int    biClrImportant;
			};

			void Image3D::SaveBmp(const char * path)
			{
				for (unsigned int frame = 0; frame < m_nbFrames; ++frame)
				{
					string extension = ".bmp";
					string fileName = path;
					char frameVal[10];
					itoa(frame, frameVal, 10);
					fileName += frameVal;
					fileName += extension;
					FILE* pFile = fopen(fileName.c_str(),"wb+");

					BitmapFileHeader oFileHeader;
					BitmapInfoHeader oInfoHeader;

					oInfoHeader.biWidth  = GetNbColumns();
					oInfoHeader.biHeight = GetNbRows();

					//We compute stride sizes. A stride must be a factor
					//of 4.
					int StrideSize = oInfoHeader.biWidth * 3;
					if((oInfoHeader.biWidth*3)%4)
					{
						StrideSize += 4-((oInfoHeader.biWidth*3)%4);
					}

					//Only 24 bit mot is encoded (1 char per color components)
					//other modes require a palette, which would be a big more
					//complicated here.
					oInfoHeader.biBitCount  = 24;
					oInfoHeader.biSizeImage = StrideSize * oInfoHeader.biHeight;

					//Offset & size. (File header = 14 bytes, File info = 40 bytes)
					oFileHeader.bfOffBits = 54;
					oFileHeader.bfSize =    54 + sizeof(char) * 
						StrideSize * 
						oInfoHeader.biHeight;

					unsigned char * pBuffer = new unsigned char[StrideSize];

					//Write header information in the bmp file.
					oFileHeader.Write(pFile);
					oInfoHeader.Write(pFile);

					//Write raster data in the bmp file.
					//The y axis is inverted in bmp files, this is why we're
					//copying lines backward.
					for(int i = oInfoHeader.biHeight-1 ;i >=0; --i)
					{
						for(int j = 0; j < oInfoHeader.biWidth; ++j)
						{
							//ColorRGB PixelColor = aImage.GetRasterData()[i*oInfoHeader.biWidth + j];
							float value = GetValue(j,i,frame);
							//PixelColor.Clamp();
							unsigned char valueChar =  (unsigned char)(value*255);
							pBuffer[j*3]    = valueChar;
							pBuffer[j*3+1]  = valueChar;
							pBuffer[j*3+2]  = valueChar;
						}
						fwrite(pBuffer,StrideSize,1,pFile);
					}

					delete[] pBuffer;

					fclose(pFile);
				}
			}
		}
	}

}