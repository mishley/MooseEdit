// @ZBS {
//		*MODULE_NAME zgranny
//		+DESCRIPTION {
//			A wrapper around granny
//		}
//		*PORTABILITY win32
//		*SDK_DEPENDS granny
//		*REQUIRED_FILES zgranny.cpp zgranny.h
//		*VERSION 1.0
//		+HISTORY {
//		}
//		+TODO {
//		}
//		*SELF_TEST no
//		*PUBLISH no
// }

// OPERATING SYSTEM specific includes:

// SDK includes:
#define GLEW_STATIC
#include <gl/glew.h>
// STDLIB includes:
#include "string.h"
#include "assert.h"
#include "stdlib.h"
#ifdef WIN32
#include "malloc.h"
#endif
// MODULE includes:
#include "zgranny.h"
#include <stdio.h>
#include <windows.h>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

granny_data_type_definition *GrannyPNT332VertexType = *(granny_data_type_definition **)GetProcAddress(LoadLibraryW(L"granny2.dll"), "GrannyPNT332VertexType");
granny_data_type_definition *GrannyPWNGBT343332VertexType = *(granny_data_type_definition **)GetProcAddress(LoadLibraryW(L"granny2.dll"), "GrannyPWNGBT343332VertexType");
granny_data_type_definition *GrannyPNGBT33332VertexType = *(granny_data_type_definition **)GetProcAddress(LoadLibraryW(L"granny2.dll"), "GrannyPNGBT33332VertexType");

//typedef void (*glCompressedTexImage2D_t)(GLenum target, 	GLint level, 	GLenum internalformat, 	GLsizei width, 	GLsizei height, 	GLint border, 	GLsizei imageSize, 	const GLvoid * data);
//glCompressedTexImage2D_t glCompressedTexImage2D = (glCompressedTexImage2D_t)wglGetProcAddress("glCompressedTexImage2D");

//void loadTexture(const GLubyte *pixelBuffer, int bufferSize, int width, int height, GLuint format) {
//	glBindTexture( GL_TEXTURE_2D, 0 );

//	glCompressedTexImage2D(
//	   GL_TEXTURE_2D, 0, format, width, height, 0,
//	   bufferSize, pixelBuffer
//   );
////	glTexImage2D(
////	   GL_TEXTURE_2D, 0, format, width, height, 0,
////	   format, GL_UNSIGNED_BYTE, pixelBuffer
////   );

//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//}
#include <iostream>
void loadTexture(const GLubyte *pixelBuffer, int bufferSize, int width, int height, GLuint format) {
	//	if (bufferSize == 0)
	//		return;
	
	//	std::cout<<"info = "<<bufferSize<<' '<<width<<' '<<height<<'\n';
	//	char buf[256];
	//	sprintf(buf, "info = %i %i %i", bufferSize, width, height);
	//	MessageBoxA(0, buf, 0, 0);
	//	int m_NbMipmaps = 1;
	//	int m_Width = width;
	//	int m_Height = height;
	//	// Missing mipmaps won't be a problem anymore.
	//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(m_NbMipmaps) - 1);
	
	//	// Upload each mipmap
	//	size_t Offset = 0;
	//	size_t Width = m_Width;
	//	size_t Height = m_Height;
	
	//	glBindTexture( GL_TEXTURE_2D, 0 );
	
	//	for (size_t i = 0; (i < m_NbMipmaps) && ((Width != 0) || (Height != 0)); ++i) {
	
	//		//size_t BufSize = ((Width + 3) / 4) * ((Height + 3) / 4) * m_BlockSize;
	
	//		glCompressedTexImage2D(GL_TEXTURE_2D, GLint(i), format, GLsizei(Width), GLsizei(Height), 0, bufferSize, pixelBuffer);
	
	//		//Offset += BufSize;
	//		if ((Width /= 2) == 0) Width = 1;
	//		if ((Height /= 2) == 0) Height = 1;
	//	}
	
	//	return;
}

//void zGrannyCreateTexture( ZGrannyTexture *texture, granny_texture *grannyTexture ) {
//   /* The name of the ZGrannyTexture is just the file name that
//      the ZGrannyTexture came from.  I'll use this later (in zGrannyFindTexture())
//      to match ZGrannyTexture references to the textures I create here. */
//   texture->name = (char *)grannyTexture->FromFileName;

//   // Loop over all the MIP levels and fill them.
//   if( (grannyTexture->TextureType == GrannyColorMapTextureType) && (grannyTexture->ImageCount == 1) ) {
//	   // Grab the single image
//	   granny_texture_image *grannyImage = &grannyTexture->Images[0];

//	   int width = grannyTexture->Width;
//	   int height = grannyTexture->Height;
//	   if( grannyImage->MIPLevelCount > 0 ) {
//		   granny_texture_mip_level &GrannyMIPLevel = grannyImage->MIPLevels[0];

//		   glGenTextures(1 , &texture->textureHandle );
//		   if( texture->textureHandle ) {
//			   glBindTexture( GL_TEXTURE_2D, texture->textureHandle );

//			   int hasAlpha = GrannyTextureHasAlpha( grannyTexture );
//			   unsigned char *pixelBuffer = new unsigned char[ width * height * 4 ];

//			   /* GrannyGetImageInFormat takes any arbitrarily formatted
//			      source ZGrannyTexture, including Bink-compressed textures, and
//			      spits them out in the RGBA format of your choice.  In this
//			      case we pick either RGBA8888 (if the ZGrannyTexture has alpha) or
//			      BGR888, since that's how we submit the OpenGL ZGrannyTexture. */
//			   GrannyCopyTextureImage(
//				   grannyTexture, 0, 0,
//				   hasAlpha ? GrannyRGBA8888PixelFormat :
//				   GrannyRGB888PixelFormat,
//				   width, height,
//				   width * (hasAlpha ? 4 : 3),
//				   pixelBuffer
//			   );

//			   glTexImage2D(
//				   GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width, height, 0,
//				   hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer
//			   );

//			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

//			   delete [] pixelBuffer;
//		   }
//	   }
//   }	 
//   else {
//	   /* I don't handle cube maps or other whacky varieties of
//	      ZGrannyTexture maps in this sample app, but if you wanted to,
//	      you'd do it here. */
//	   assert(0);
//	   //ErrorMessage("This sample only works with single-image ColorMapTextureType textures");
//   }
//}

void zGrannyCreateModel( ZGrannyModel *model, ZGrannyScene *inScene, granny_model *grannyModel, std::vector<GLuint > &textures) {
	/* First, I grab the bone count for the ZGrannyModel and check to see
	  if it's the biggest I've seen so far.  If it is, I record it.
	  This is used back in OSStartup() to determine how big to make
	  the shared local pose buffer. */
	int boneCount = grannyModel->Skeleton->BoneCount;
	if( inScene->maxBoneCount < boneCount ) {
		inScene->maxBoneCount = boneCount;
	}
	model->skeleton = grannyModel->Skeleton;
	/* Now I ask Granny for two objects I'm going to use to animate
	  the ZGrannyModel.  The first is the granny_model_instance, which keeps
	  track of what animations are playing on the ZGrannyModel... */
	model->grannyInstance = GrannyInstantiateModel( grannyModel );
	
	/* ... the second is the granny_world_pose, which is a buffer that
	  stores the world-space matrices for all the bones of the ZGrannyModel
	  so that I can use them for rendering (or collision detection,
	  etc.) at any time. */
	model->worldPose = GrannyNewWorldPose( boneCount );
	
	model->localPose = GrannyNewLocalPose( boneCount );
	
	/* Now, I loop through all the meshes in the ZGrannyModel and process
	  them. */
	model->meshCount = grannyModel->MeshBindingCount;
	model->meshes = new ZGrannyMesh[ model->meshCount ];
	for( int i = 0; i < model->meshCount; ++i ) {
		zGrannyCreateMesh(
					&model->meshes[i],
					grannyModel->MeshBindings[i].Mesh,
					textures,
					model->grannyInstance, inScene
					);
	}
}

void zGrannyCreateMesh( ZGrannyMesh *mesh, granny_mesh *grannyMesh, std::vector<GLuint > &textures, granny_model_instance *inModel, ZGrannyScene *inScene ) {
	mesh->grannyMesh = grannyMesh;
	
	/* First I create the Granny binding for this ZGrannyMesh.	The binding
	  is basically a table that says what bone slots of the ZGrannyMesh go
	  with which bones of the ZGrannyModel.  It's used during rendering to
	  pull the correct matrices from the skeleton to use for
	  deformation (or just to load the correct single transform in
	  the case of rigid meshes). */
	granny_skeleton *skeleton = GrannyGetSourceSkeleton( inModel );
	mesh->grannyBinding = GrannyNewMeshBinding( grannyMesh, skeleton, skeleton );
	
	/* Because I use GL display lists for rigid meshes, before processing
	  the vertex data, I make sure I bind the textures.  This is to
	  make sure the zGrannyRenderMesh() call that's used to send down the
	  data for the display can access this ZGrannyMesh's ZGrannyTexture table. */
	mesh->textureCount = grannyMesh->MaterialBindingCount;
	mesh->textureReferences = new ZGrannyTexture *[ mesh->textureCount ];
	for( int i = 0; i < mesh->textureCount; ++i ) {
		mesh->textureReferences[i] = zGrannyFindTexture( inScene, grannyMesh->MaterialBindings[i].Material );
	}
	
	int vertexCount = GrannyGetMeshVertexCount( grannyMesh );
	
	/* Now, I process the vertex data. */
	//if( GrannyMeshIsRigid(grannyMesh) ) {
	if (false) {
		/* It's a rigid ZGrannyMesh, so I can store the whole thing in a 
		  (possibly card resident) display list. */
		granny_pngbt33332_vertex *tempVertices = new granny_pngbt33332_vertex[vertexCount];
		
		/* GrannyCopyMeshVertices can do arbitrary vertex format
		  conversion, so in this case I just request that, whatever
		  format the ZGrannyMesh is in, it gets converted to 3-float
		  position, 3-float normal, 2-float ZGrannyTexture coordinate
		  format.	I use the pre-defined layout
		  GrannyPNT332VertexLayout for this, but you can also define
		  your own, so you're not limited to Granny's presets if you
		  want to use other more fanciful vertex formats (more
		  ZGrannyTexture coordinates, tangent spaces, etc., can all be in
		  there). */
		
		GrannyCopyMeshVertices( grannyMesh, GrannyPNGBT33332VertexType, tempVertices );
		
		
		mesh->displayList = glGenLists(1);
		if( mesh->displayList ) {
			glNewList( mesh->displayList, GL_COMPILE );
			
			glEnableClientState( GL_VERTEX_ARRAY );
			glEnableClientState( GL_NORMAL_ARRAY );
			glEnableClientState( GL_TEXTURE_COORD_ARRAY );
			
			zGrannyRenderMesh3( mesh, tempVertices, textures, 0, 0, 0 );
			
			glDisableClientState( GL_VERTEX_ARRAY );
			glDisableClientState( GL_NORMAL_ARRAY );
			glDisableClientState( GL_TEXTURE_COORD_ARRAY );
			
			glEndList();
		}
		else {
			assert(0);
			//ErrorMessage( "Unable to allocate GL display list for ZGrannyMesh %s - this ZGrannyMesh will not render properly.", grannyMesh->Name );
		}
		
		delete [] tempVertices;
		
		// Since this is a rigid ZGrannyMesh, we won't need a deformer.
		mesh->grannyDeformer = 0;
	}
	else {
		/* ... and then I create a Granny deformer for this ZGrannyMesh.  I
		  ask for deformations for the position and normal in this
		  case, since that's all I've got, but I could also ask for
		  deformations of the tangent space if I was doing bump
		  mapping. */
		
//		mesh->grannyDeformer = GrannyNewMeshDeformer(
//					GrannyGetMeshVertexType(grannyMesh), GrannyPNT332VertexType,
//					GrannyDeformPositionNormal, GrannyAllowUncopiedTail
//					);
		mesh->grannyDeformer = 0;
		
		if( !mesh->grannyDeformer ) {
			//assert(0);
			//ErrorMessage( "Granny didn't find a matching deformer for the vertex format used by ZGrannyMesh \"%s\".  This ZGrannyMesh won't be rendered properly.", grannyMesh->Name );
		}
	}
}

ZGrannyTexture *zGrannyFindTexture( ZGrannyScene *scene, granny_material *grannyMaterial ) {
	/* I ask Granny for the diffuse color ZGrannyTexture of this material,
	  if there is one.  For a more complicated shader system,
	  you would probably ask for more maps (like bump maps) and
	  maybe query extra properties like shininess and so on. */
	granny_texture *grannyTexture = GrannyGetMaterialTextureByType( grannyMaterial, GrannyDiffuseColorTexture );
	if( grannyTexture ) {
		// Look through all the textures in the file for a match-by-name.
		for(int i = 0; i < scene->textureCount; ++i ) {
			ZGrannyTexture &texture = scene->textures[i];
			if( strcmp(texture.name, grannyTexture->FromFileName) == 0 ) {
				return(&texture);
			}
		}
	}
	
	return(0);
}

bool shown2 = false;
int shownCount = 0;
void zGrannyRenderModel( ZGrannyScene *inScene, ZGrannyModel *model, std::vector<GLuint > &textures, VertexRGB *vertexRgb, VertexRGB *vertexRgb2, GlShaderProgram *shaderProgram, renderInfo_t *renderInfo ) {
	/* Before I do any rendering, I enable the arrays for the vertex
	  format I'm using.  You could do this once for the entire app,
	  since I never render anything else, but I figured it'd me more
	  instructive to put it here where I actually do the rendering. */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	/* Since I'm going to need it constantly, I dereference the composite
	  transform buffer for the ZGrannyModel's current world-space pose.  This
	  buffer holds the transforms that move vertices from the position
	  in which they were modeled to their current position in world space. */
	granny_matrix_4x4 *compositeBuffer = GrannyGetWorldPoseComposite4x4Array( model->worldPose );
	
	// Render all the meshes.
	for( int i = 0; i < model->meshCount; ++i ) {
		ZGrannyMesh &mesh = model->meshes[i];
		
		// Dereference the index table that maps ZGrannyMesh bone indices to
		// bone indices in the ZGrannyModel.
		int *toBoneIndices = (int *)GrannyGetMeshBindingToBoneIndices( mesh.grannyBinding );
		
		// Load the ZGrannyMesh's vertices, or deform into a temporary
		// buffer and load those, depending on whether the ZGrannyMesh is
		// rigid or not.
		int vertexCount = GrannyGetMeshVertexCount( mesh.grannyMesh );
		//if( GrannyMeshIsRigid(mesh.grannyMesh) ) {
		if (false) {
			// It's a rigid ZGrannyMesh, so I use the display list we've
			// previously created for it.
			glPushMatrix();
			granny_matrix_4x4 *transform = &compositeBuffer[toBoneIndices[0]];
			glMultMatrixf( (GLfloat *)transform );
			
			glCallList( mesh.displayList );
			
			glPopMatrix();
		}
		//else if( mesh.grannyDeformer ) {
		else if( true ) {
			// Tell Granny to deform the vertices of the ZGrannyMesh with the
			// current world pose of the ZGrannyModel, and dump the results
			// into the mutable vertex buffer.
			
			if (mesh.grannyDeformer) {
				granny_pnt332_vertex *vertices = new granny_pnt332_vertex[vertexCount];
				GrannyDeformVertices(
							mesh.grannyDeformer, 
							toBoneIndices, (float *)compositeBuffer,
							vertexCount,
							GrannyGetMeshVertices( mesh.grannyMesh ),
							vertices
							);
				if (shown2 == false) {\
					shown2 = true;
					for (int i=0; i<20; ++i) {
						//std::cout<<"pos = "<<vertices[i].Position[0]<<' '<<vertices[i].Position[1]<<' '<<vertices[i].Position[2]<<'\n';
					}
				}
				zGrannyRenderMesh2( &mesh, vertices, textures, vertexRgb, shaderProgram );
				delete[] vertices;
			} else {
				//granny_pwngbt343332_vertex *vertices2 = (granny_pwngbt343332_vertex *)GrannyGetMeshVertices( mesh.grannyMesh );
				granny_pwngbt343332_vertex *vertices2 = new granny_pwngbt343332_vertex[vertexCount];
				GrannyCopyMeshVertices( mesh.grannyMesh, GrannyPWNGBT343332VertexType, vertices2 );
				++shownCount;
				if (shownCount == 50) {
					std::cout<<"no deformer"<<'\n';
					std::cout<<mesh.grannyMesh->Name<<'\n';
					for (int i=0; i<20; ++i) {
						//std::cout<<"pos = "<<vertices2[i].Position[0]<<' '<<vertices2[i].Position[1]<<' '<<vertices2[i].Position[2]<<'\n';
					}
				}
				zGrannyRenderMesh( &mesh, vertices2, textures, vertexRgb, vertexRgb2, shaderProgram, renderInfo );
				delete[] vertices2;
			}
		}
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void zGrannyRenderMesh3( ZGrannyMesh *mesh, granny_pngbt33332_vertex *vertices, std::vector<GLuint > &textures, VertexRGB *rgbData, GlShaderProgram *shaderProgram) {
	glVertexPointer( 3, GL_FLOAT, sizeof(*vertices), vertices->Position );
	glNormalPointer( GL_FLOAT, sizeof(*vertices), vertices->Normal );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(*vertices), vertices->UV );
	
	if (shaderProgram != 0) {
		shaderProgram->set3dVectorAttribute("vertex", sizeof(*vertices), vertices->Position);
		shaderProgram->set3dVectorAttribute("normal", sizeof(*vertices), vertices->Normal);
		shaderProgram->set2dVectorAttribute("uv_coord", sizeof(*vertices), vertices->UV);
		
		GLfloat modelViewMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
		shaderProgram->setUniformMatrix4x4("_mv", modelViewMatrix);
		GLfloat projectionMatrix[16];
		glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
		shaderProgram->setUniformMatrix4x4("_proj", projectionMatrix);
		shaderProgram->setUniformInt("color_texture", 0);
		shaderProgram->setUniformInt("normal_texture", 1);
		shaderProgram->setUniformInt("mask_texture", 2);
	}
	
	/* Now both the indices and vertices are loaded, so I can
	  render.	I grab the material groups and spin over them,
	  changing to the appropriate ZGrannyTexture and rendering each batch.
	  A more savvy rendering loop might have instead built a
	  sorted list of material groups to minimize ZGrannyTexture changes,
	  etc., but this is the most basic way to render. */
	int indexSize = GrannyGetMeshBytesPerIndex( mesh->grannyMesh );
	unsigned char *Indices = (unsigned char *)GrannyGetMeshIndices( mesh->grannyMesh );
	int groupCount = GrannyGetMeshTriangleGroupCount( mesh->grannyMesh );
	granny_tri_material_group *group = GrannyGetMeshTriangleGroups( mesh->grannyMesh );
	while( groupCount-- ) {
		if( group->MaterialIndex < mesh->textureCount ) {
			ZGrannyTexture *texture = mesh->textureReferences[group->MaterialIndex];
			if( texture ) {
				glBindTexture( GL_TEXTURE_2D, texture->textureHandle );
			}
		}
		for (int i=0; i<textures.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
		
		glDrawElements(
					GL_TRIANGLES,
					group->TriCount*3,
					(indexSize == 4) ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT,
					&Indices[group->TriFirst*3*indexSize]
				);
		
		++group;
	}
}

void zGrannyRenderMesh2( ZGrannyMesh *mesh, granny_pnt332_vertex *vertices, std::vector<GLuint > &textures, VertexRGB *rgbData, GlShaderProgram *shaderProgram) {
	glVertexPointer( 3, GL_FLOAT, sizeof(*vertices), vertices->Position );
	glNormalPointer( GL_FLOAT, sizeof(*vertices), vertices->Normal );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(*vertices), vertices->UV );
	
	if (shaderProgram != 0) {
		shaderProgram->set3dVectorAttribute("vertex", sizeof(*vertices), vertices->Position);
		shaderProgram->set3dVectorAttribute("normal", sizeof(*vertices), vertices->Normal);
		shaderProgram->set2dVectorAttribute("uv_coord", sizeof(*vertices), vertices->UV);
		
		GLfloat modelViewMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
		shaderProgram->setUniformMatrix4x4("_mv", modelViewMatrix);
		GLfloat projectionMatrix[16];
		glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
		shaderProgram->setUniformMatrix4x4("_proj", projectionMatrix);
		shaderProgram->setUniformInt("color_texture", 0);
		shaderProgram->setUniformInt("normal_texture", 1);
		shaderProgram->setUniformInt("mask_texture", 2);
	}
	
	/* Now both the indices and vertices are loaded, so I can
	  render.	I grab the material groups and spin over them,
	  changing to the appropriate ZGrannyTexture and rendering each batch.
	  A more savvy rendering loop might have instead built a
	  sorted list of material groups to minimize ZGrannyTexture changes,
	  etc., but this is the most basic way to render. */
	int indexSize = GrannyGetMeshBytesPerIndex( mesh->grannyMesh );
	unsigned char *Indices = (unsigned char *)GrannyGetMeshIndices( mesh->grannyMesh );
	int groupCount = GrannyGetMeshTriangleGroupCount( mesh->grannyMesh );
	granny_tri_material_group *group = GrannyGetMeshTriangleGroups( mesh->grannyMesh );
	while( groupCount-- ) {
		if( group->MaterialIndex < mesh->textureCount ) {
			ZGrannyTexture *texture = mesh->textureReferences[group->MaterialIndex];
			if( texture ) {
				glBindTexture( GL_TEXTURE_2D, texture->textureHandle );
			}
		}
		for (int i=0; i<textures.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
		
		glDrawElements(
					GL_TRIANGLES,
					group->TriCount*3,
					(indexSize == 4) ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT,
					&Indices[group->TriFirst*3*indexSize]
				);
		
		++group;
	}
}
#include <sstream>
void zGrannyRenderMesh( ZGrannyMesh *mesh, granny_pwngbt343332_vertex *vertices, std::vector<GLuint > &textures, VertexRGB *vertexRgb, VertexRGB *vertexRgb2, GlShaderProgram *shaderProgram, 
						renderInfo_t *renderInfo) {
	glVertexPointer( 3, GL_FLOAT, sizeof(*vertices), vertices->Position );
	glNormalPointer( GL_FLOAT, sizeof(*vertices), vertices->Normal );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(*vertices), vertices->UV );

	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::ostringstream ss;
		ss<<"err2: "<<gluErrorString(err);
		std::cout<<ss.str()<<'\n';
	}
	if (shaderProgram != 0) {
		shaderProgram->set3dVectorAttribute("inPosition0", sizeof(*vertices), vertices->Position);
		shaderProgram->set3dVectorAttribute("inNormal0", sizeof(*vertices), vertices->Normal);
		shaderProgram->set2dVectorAttribute("inTexCoord0", sizeof(*vertices), vertices->UV);
		shaderProgram->set3dVectorAttribute("inTangent0", sizeof(*vertices), vertices->Tangent);
		shaderProgram->set3dVectorAttribute("inBinormal0", sizeof(*vertices), vertices->Binormal);
		//shaderProgram->set4dVectorAttributeUB("inBlendIndices0", sizeof(*vertices), vertices->BoneIndices);
		//shaderProgram->set4dVectorAttributeUB("inBlendWeight0", sizeof(*vertices), vertices->BoneWeights);
		
		int vertexCount = GrannyGetMeshVertexCount(mesh->grannyMesh);
		float *boneIndices = new float[4 * vertexCount];
		float *boneWeights = new float[4 * vertexCount];
		for (int i=0; i<vertexCount; ++i) {
//			boneIndices[i*4 + 0] = (float)vertices->BoneIndices[0];
//			boneIndices[i*4 + 1] = (float)vertices->BoneIndices[1];
//			boneIndices[i*4 + 2] = (float)vertices->BoneIndices[2]; //need bone indices from male body, not from current model
//			boneIndices[i*4 + 3] = (float)vertices->BoneIndices[3];
			boneIndices[i*4 + 0] = 1.0f;
			boneIndices[i*4 + 1] = 1.0f;
			boneIndices[i*4 + 2] = 1.0f;
			boneIndices[i*4 + 3] = 1.0f;
			boneWeights[i*4 + 0] = vertices->BoneWeights[0]/255.0f;
			boneWeights[i*4 + 1] = vertices->BoneWeights[1]/255.0f;
			boneWeights[i*4 + 2] = vertices->BoneWeights[2]/255.0f;
			boneWeights[i*4 + 3] = vertices->BoneWeights[3]/255.0f;
		}
		shaderProgram->set4dVectorAttribute("inBlendIndices0", 0, boneIndices);
		shaderProgram->set4dVectorAttribute("inBlendWeight0", sizeof(float)*4, boneWeights);
		delete[] boneIndices;
		delete[] boneWeights;
		
		if (renderInfo != 0) {
			if (renderInfo->model != 0) {
				shaderProgram->setUniformMatrix4x4("WorldMatrix", glm::value_ptr(*renderInfo->model));
			}
			if (renderInfo->model != 0 && renderInfo->view != 0) {
				GLfloat modelViewMatrix[16];
				glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
				glm::mat4 modelView = *renderInfo->view * *renderInfo->model;
				shaderProgram->setUniformMatrix4x4("global_ModelView", glm::value_ptr(modelView));
			}
			GLfloat projectionMatrix[16];
			glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
			if (renderInfo->projection != 0) {
				shaderProgram->setUniformMatrix4x4("global_Projection", glm::value_ptr(*renderInfo->projection));
			}
			if (renderInfo->view != 0 && renderInfo->projection != 0) {
				glm::mat4 viewProjection = *renderInfo->projection * *renderInfo->view;
				shaderProgram->setUniformMatrix4x4("global_ViewProjection", glm::value_ptr(viewProjection));
			}
			
			if (renderInfo->viewInfo != 0) {
				shaderProgram->setUniformVec4("global_ViewInfo", glm::value_ptr(*renderInfo->viewInfo));
			}
			if (renderInfo->data != 0) {
				shaderProgram->setUniformVec4("global_Data", glm::value_ptr(*renderInfo->data));
			}
			
			if (renderInfo->viewPos != 0) {
				shaderProgram->setUniformVec4("global_ViewPos", glm::value_ptr(*renderInfo->viewPos));
			}
			if (renderInfo->lightPropertyMatrix != 0) {
				shaderProgram->setUniformMatrix4x4("global_LightPropertyMatrix", glm::value_ptr(*renderInfo->lightPropertyMatrix));
			}
			if (renderInfo->fogPropertyMatrix != 0) {
				shaderProgram->setUniformMatrix4x3("global_FogPropertyMatrix", glm::value_ptr(*renderInfo->fogPropertyMatrix));
			}
			
			shaderProgram->setUniformFloat("_OpacityFade", renderInfo->opacityFade);
			shaderProgram->setUniformFloat("FloatParameter_CharacterHeight", renderInfo->characterHeight);
			shaderProgram->setUniformFloat("FloatParameter_CharacterHeightContrast", renderInfo->characterHeightContrast);
			shaderProgram->setUniformFloat("FloatParameter_BackLightContrast", renderInfo->backLightContrast);
			shaderProgram->setUniformFloat("FloatParameter_BackLightIntensity", renderInfo->backLightIntensity);
			
			if (renderInfo->color1 != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color1", glm::value_ptr(*renderInfo->color1));
			}
			if (renderInfo->color2 != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color2", glm::value_ptr(*renderInfo->color2));
			}
			if (renderInfo->color3 != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color3", glm::value_ptr(*renderInfo->color3));
			}
			if (renderInfo->color4 != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color4", glm::value_ptr(*renderInfo->color4));
			}
			if (renderInfo->color5 != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color5", glm::value_ptr(*renderInfo->color5));
			}
			
			shaderProgram->setUniformFloat("FloatParameter_FillLightContrast", renderInfo->fillLightContrast);
			shaderProgram->setUniformFloat("FloatParameter_FillLightIntensity", renderInfo->fillLightIntensity);
			shaderProgram->setUniformFloat("FloatParameter_RimLightContrast", renderInfo->rimLightContrast);
			shaderProgram->setUniformFloat("FloatParameter_RimLightIntensity", renderInfo->rimLightIntensity);

			if (renderInfo->color1Specular != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color1_Specular", glm::value_ptr(*renderInfo->color1Specular));
			}
			if (renderInfo->color2Specular != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color2_Specular", glm::value_ptr(*renderInfo->color2Specular));
			}
			if (renderInfo->color3Specular != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color3_Specular", glm::value_ptr(*renderInfo->color3Specular));
			}
			if (renderInfo->color4Specular != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color4_Specular", glm::value_ptr(*renderInfo->color4Specular));
			}
			if (renderInfo->color5Specular != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color5_Specular", glm::value_ptr(*renderInfo->color5Specular));
			}
			
			shaderProgram->setUniformFloat("FloatParameter_Gloss", renderInfo->specularGloss);
			shaderProgram->setUniformFloat("FloatParameter_SpecularMultiplier", renderInfo->specularMultiplier);
			shaderProgram->setUniformFloat("FloatParameter_GlowMultiploer", renderInfo->glowMultiplier);
			
			if (renderInfo->itemColor != 0) {
				shaderProgram->setUniformVec4("Vector4Parameter_Color", glm::value_ptr(*renderInfo->itemColor));
			}
			
			const int boneMatrixSize = 4*3;
			GLfloat *boneMatrices = new GLfloat[boneMatrixSize*BONE_MATRICES_COUNT];
			for (int i=0; i<BONE_MATRICES_COUNT; ++i) {
				glm::mat4x3 *boneMatrix = renderInfo->boneMatrices[i];
				GLfloat *boneMatrixPosition = &boneMatrices[i * boneMatrixSize];
				if (boneMatrix != 0) {
					memcpy(boneMatrixPosition, glm::value_ptr(*boneMatrix), sizeof(GLfloat) * boneMatrixSize);
				} else {
					glm::mat4x3 ident(1.0);
					memcpy(boneMatrixPosition, glm::value_ptr(ident), sizeof(GLfloat) * boneMatrixSize);
				}
			}
			shaderProgram->setUniformMatrixArray4x3("BoneMatrices", boneMatrices, BONE_MATRICES_COUNT);
			delete[] boneMatrices;
		}
		shaderProgram->setUniformInt("Texture2DParameter_DM", 0);
		shaderProgram->setUniformInt("Texture2DParameter_NM", 1);
		shaderProgram->setUniformInt("Texture2DParameter_SM", 2);
		shaderProgram->setUniformInt("Texture2DParameter_MSK", 3);
		if (vertexRgb != 0) {
			GLfloat vec[4];
			vec[0] = vertexRgb->r/255.0;
			vec[1] = vertexRgb->g/255.0;
			vec[2] = vertexRgb->b/255.0;
			vec[3] = vertexRgb->a/255.0;
			shaderProgram->setUniformVec4("skinColor", vec);
			shaderProgram->setUniformFloat("useForeColor", 1.0f);
		} else {
			shaderProgram->setUniformFloat("useForeColor", 0.0f);
		}
		if (vertexRgb2 != 0) {
			GLfloat vec[4];
			vec[0] = vertexRgb2->r/255.0;
			vec[1] = vertexRgb2->g/255.0;
			vec[2] = vertexRgb2->b/255.0;
			vec[3] = vertexRgb2->a/255.0;
			shaderProgram->setUniformVec4("backColor", vec);
			shaderProgram->setUniformFloat("useBackColor", 1.0f);
		} else {
			shaderProgram->setUniformFloat("useBackColor", 0.0f);
		}
		glGetError(); //clear errors
	}
	
	/* Now both the indices and vertices are loaded, so I can
	  render.	I grab the material groups and spin over them,
	  changing to the appropriate ZGrannyTexture and rendering each batch.
	  A more savvy rendering loop might have instead built a
	  sorted list of material groups to minimize ZGrannyTexture changes,
	  etc., but this is the most basic way to render. */
	int indexSize = GrannyGetMeshBytesPerIndex( mesh->grannyMesh );
	unsigned char *Indices = (unsigned char *)GrannyGetMeshIndices( mesh->grannyMesh );
	int groupCount = GrannyGetMeshTriangleGroupCount( mesh->grannyMesh );
	granny_tri_material_group *group = GrannyGetMeshTriangleGroups( mesh->grannyMesh );
	while( groupCount-- ) {
		if( group->MaterialIndex < mesh->textureCount ) {
			ZGrannyTexture *texture = mesh->textureReferences[group->MaterialIndex];
			if( texture ) {
				glBindTexture( GL_TEXTURE_2D, texture->textureHandle );
			}
		}
		for (int i=0; i<textures.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
		
		glDrawElements(
					GL_TRIANGLES,
					group->TriCount*3,
					(indexSize == 4) ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT,
					&Indices[group->TriFirst*3*indexSize]
				);
		
		++group;
	}
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::ostringstream ss;
		ss<<"err4: "<<gluErrorString(err);
		std::cout<<ss.str()<<'\n';
	}
}

void zGrannyRenderSkeleton( granny_skeleton *skeleton, granny_world_pose *worldPose ) {
	int boneCount = skeleton->BoneCount;
	granny_bone *bones = skeleton->Bones;
	
	// Draw points at all the bone locations
	glColor3f( 1.0f, 1.0f, 1.0f );
	glBegin( GL_POINTS );
	for( int i = 0; i < boneCount; ++i ) {
		float *transform = GrannyGetWorldPose4x4( worldPose, i );
		glVertex3fv(&transform[12]);
	}
	glEnd();
	
	glBegin(GL_LINES);
	for( int i = 0; i < boneCount; ++i ) {
		float *transform = GrannyGetWorldPose4x4( worldPose, i );
		
		// Draw a line connecting each child bone to its parent
		if( bones[i].ParentIndex != GrannyNoParentBone ) {
			float *parentTransform = GrannyGetWorldPose4x4( worldPose, bones[i].ParentIndex );
			
			glColor3f( 1.0f, 1.0f, 1.0f );
			glVertex3fv( &transform[12] );
			
			glColor3f( 0.7f, 0.7f, 0.7f );
			glVertex3fv( &parentTransform[12] );
		}
		
		// Draw a scaled axis system at each of the bones
		float scale = 10.0f;
		
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex3fv( &transform[12] );
		glVertex3f( transform[12] + scale*transform[0], transform[13] + scale*transform[1], transform[14] + scale*transform[2] );
		
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3fv( &transform[12] );
		glVertex3f( transform[12] + scale*transform[4], transform[13] + scale*transform[5], transform[14] + scale*transform[6] );
		
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex3fv( &transform[12] );
		glVertex3f( transform[12] + scale*transform[8], transform[13] + scale*transform[9], transform[14] + scale*transform[10] );
	}
	glEnd();
}

// TODO:
// I want to be able to import multiple files into a scene
// and then update and render that scene how I want
// I want to be able to fetch model pointers conveniently out of the scene
// and manipulate them bu name.

ZGrannyScene *zGrannyCreateScene( const char *filename, std::vector<GLuint > &textures ) {
	ZGrannyScene *scene = new ZGrannyScene;
	memset( scene, 0, sizeof(*scene) );
	scene->shouldRender = true;
	
	scene->loadedFile = GrannyReadEntireFile( filename );
	assert( scene->loadedFile );
	
	granny_file_info *fileInfo = GrannyGetFileInfo( scene->loadedFile );
	//            GlobalScene.TextureCount = FileInfo->TextureCount;
	//            GlobalScene.Textures = new texture[GlobalScene.TextureCount];
	//            {for(int TextureIndex = 0;
	//                 TextureIndex < GlobalScene.TextureCount;
	//                 ++TextureIndex)
	//            {
	//                CreateTexture(&GlobalScene.Textures[TextureIndex],
	//                              FileInfo->Textures[TextureIndex]);
	//            }}            
	
	scene->modelCount = fileInfo->ModelCount;
	scene->models = new ZGrannyModel[scene->modelCount];
	memset( scene->models, 0, sizeof(ZGrannyModel)*scene->modelCount );
	for( int i = 0; i < scene->modelCount; ++i ) {
		// Create the model
		granny_model *grannyModel = fileInfo->Models[i];
		ZGrannyModel *model = &scene->models[i];
		zGrannyCreateModel( model, scene, grannyModel, textures );
		
		GrannyGetModelInitialPlacement4x4( grannyModel, (float *)model->matrix );
		
		if( fileInfo->AnimationCount ) {
			granny_animation *animation = fileInfo->Animations[0];
			granny_control *control = GrannyPlayControlledAnimation( 0.0f, animation, model->grannyInstance );
			if( control ) {
				GrannySetControlLoopCount( control, 0 );
				GrannyFreeControlOnceUnused( control );
			}
		}
		
	}
	
	// redo:
	scene->sharedLocalPose = GrannyNewLocalPose( scene->maxBoneCount );
	
	return scene;
}

ZGrannyScene *zGrannyCreateSceneFromMemory( const char *fileBytes, unsigned long fileSize, std::vector<GLuint > &textures ) {
	ZGrannyScene *scene = new ZGrannyScene;
	memset( scene, 0, sizeof(*scene) );
	scene->shouldRender = true;
	
	scene->loadedFile = GrannyReadEntireFileFromMemory(fileSize, (void *)fileBytes);
	assert( scene->loadedFile );
	
	granny_file_info *fileInfo = GrannyGetFileInfo( scene->loadedFile );
	//            GlobalScene.TextureCount = FileInfo->TextureCount;
	//            GlobalScene.Textures = new texture[GlobalScene.TextureCount];
	//            {for(int TextureIndex = 0;
	//                 TextureIndex < GlobalScene.TextureCount;
	//                 ++TextureIndex)
	//            {
	//                CreateTexture(&GlobalScene.Textures[TextureIndex],
	//                              FileInfo->Textures[TextureIndex]);
	//            }}            
	
	scene->modelCount = fileInfo->ModelCount;
	scene->models = new ZGrannyModel[scene->modelCount];
	memset( scene->models, 0, sizeof(ZGrannyModel)*scene->modelCount );
	for( int i = 0; i < scene->modelCount; ++i ) {
		// Create the model
		granny_model *grannyModel = fileInfo->Models[i];
		ZGrannyModel *model = &scene->models[i];
		zGrannyCreateModel( model, scene, grannyModel, textures );
		
		GrannyGetModelInitialPlacement4x4( grannyModel, (float *)model->matrix );
		
		if( fileInfo->AnimationCount ) {
			granny_animation *animation = fileInfo->Animations[0];
			granny_control *control = GrannyPlayControlledAnimation( 0.0f, animation, model->grannyInstance );
			if( control ) {
				GrannySetControlLoopCount( control, 0 );
				GrannyFreeControlOnceUnused( control );
			}
		}
		
	}
	
	// redo:
	scene->sharedLocalPose = GrannyNewLocalPose( scene->maxBoneCount );
	
	return scene;
}

std::vector<int> getBoneChildren(int boneIndex, ZGrannyModel *attachTo) {
	std::vector<int> children;
	for (int i=0; i<attachTo->skeleton->BoneCount; ++i) {
		granny_bone &bone = attachTo->skeleton->Bones[i];
		if (bone.ParentIndex == boneIndex) {
			children.push_back(i);
		}
	}
	return children;
}

bool zGrannyMakeTransformMatrices(int boneIndex, ZGrannyModel *attachTo, std::vector<glm::mat4> &transformMatrices) {
	if (attachTo == 0 || attachTo->skeleton == 0 || boneIndex >= attachTo->skeleton->BoneCount)
		return false;
	
	if (transformMatrices.size() == 0) {
		transformMatrices.resize(attachTo->skeleton->BoneCount);
	}
	
	glm::mat4 transformMatrix(1.0);
	granny_bone &bone = attachTo->skeleton->Bones[boneIndex];
	glm::vec3 scaleX = glm::make_vec3((float *)&bone.LocalTransform.ScaleShear[0]);
	glm::vec3 scaleY = glm::make_vec3((float *)&bone.LocalTransform.ScaleShear[1]);
	glm::vec3 scaleZ = glm::make_vec3((float *)&bone.LocalTransform.ScaleShear[2]);
	glm::vec3 scale = glm::vec3(glm::length(scaleX), glm::length(scaleY), glm::length(scaleZ));
	glm::quat quaternion = glm::quat(bone.LocalTransform.Orientation[0], bone.LocalTransform.Orientation[1], bone.LocalTransform.Orientation[2], bone.LocalTransform.Orientation[3]);
	glm::vec3 eulerAngles = glm::eulerAngles(quaternion);
	glm::vec3 rotation = glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	glm::vec3 translation = glm::make_vec3(&bone.LocalTransform.Position[0]);
	
	if (boneIndex == 0) {
		std::cout<<scale.x<<' '<<scale.y<<' '<<scale.z<<'\n';
		std::cout<<rotation.x<<' '<<rotation.y<<' '<<rotation.z<<'\n';
		std::cout<<translation.x<<' '<<translation.y<<' '<<translation.z<<'\n';
	}
	transformMatrix = glm::scale(transformMatrix, scale);
	transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(1.0, 0.0, 0.0)); //pitch
	transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(0.0, 1.0, 0.0)); //yaw
	transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(0.0, 0.0, 1.0)); //roll
	transformMatrix = glm::translate(transformMatrix, translation);
	if (bone.ParentIndex >= 0) {
		transformMatrix = transformMatrix * transformMatrices[bone.ParentIndex];
	}
	transformMatrices[boneIndex] = transformMatrix;
	std::vector<int> children = getBoneChildren(boneIndex, attachTo);
	std::cout<<"Bone "<<boneIndex<<'\n';
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			std::cout<<transformMatrix[i][j]<<' ';
		}
		std::cout<<'\n';
	}
	std::cout<<'\n';
	std::cout<<"expected: "<<'\n';
	glm::mat4 inverseWorld = glm::make_mat4((float *)&bone.InverseWorld4x4);
	glm::mat4 world = glm::inverse(inverseWorld);
	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			std::cout<<world[i][j]<<' ';
		}
		std::cout<<'\n';
	}
	std::cout<<'\n';
	for (int i=0; i<children.size(); ++i) {
		int childBone = children[i];
		if (!zGrannyMakeTransformMatrices(childBone, attachTo, transformMatrices)) {
			return false;
		}
	}
	//glm::mat4 inverseWorld = glm::make_mat4((float *)&bone.InverseWorld4x4);
	transformMatrices[boneIndex] = transformMatrix * inverseWorld;
	return true;
}

bool zGrannyGetAttachmentMatrix(std::string boneName, ZGrannyModel *attachTo, ZGrannyModel *toAttach, glm::mat4 &attachmentMatrix) {
	if (attachTo == 0 || attachTo->skeleton == 0)
		return false;
	
	for (int i=0; i<attachTo->skeleton->BoneCount; ++i) {
		granny_bone &bone = attachTo->skeleton->Bones[i];
		if (bone.Name == boneName) {
			GrannySampleModelAnimations(attachTo->grannyInstance,
			                                0, attachTo->skeleton->BoneCount,
			                                attachTo->localPose);
			
			granny_matrix_4x4 BaseMatrix;
			    GrannyGetWorldMatrixFromLocalPose(attachTo->skeleton,
			                                      i,
			                                      attachTo->localPose,
			                                      0,
			                                      (granny_real32*)BaseMatrix,
			                                      NULL, NULL);
			
			granny_matrix_4x4 AttachmentMatrix;
		    GrannyGetAttachmentOffset(attachTo->skeleton,
		                              i,
		                              attachTo->localPose,
		                              0,
		                              (granny_real32*)AttachmentMatrix,
		                              0, 0);
		
			attachmentMatrix = glm::inverse(glm::make_mat4((float *)&bone.InverseWorld4x4));
			return true;
		}
	}
	return false;
}

bool zGrannyGetObbCenter2(std::string boneName, ZGrannyModel *attachTo, ZGrannyModel *toAttach, GLfloat obbCenter[3]) {
	if (attachTo == 0 || attachTo->skeleton == 0)
		return false;
	
	for (int i=0; i<attachTo->skeleton->BoneCount; ++i) {
		granny_bone &bone = attachTo->skeleton->Bones[i];
		if (bone.Name == boneName) {
			GrannySampleModelAnimations(attachTo->grannyInstance,
			                                0, attachTo->skeleton->BoneCount,
			                                attachTo->localPose);
			
			granny_matrix_4x4 BaseMatrix;
			    GrannyGetWorldMatrixFromLocalPose(attachTo->skeleton,
			                                      i,
			                                      attachTo->localPose,
			                                      0,
			                                      (granny_real32*)BaseMatrix,
			                                      NULL, NULL);
			
			granny_matrix_4x4 AttachmentMatrix;
		    GrannyGetAttachmentOffset(attachTo->skeleton,
		                              i,
		                              attachTo->localPose,
		                              0,
		                              (granny_real32*)AttachmentMatrix,
		                              0, 0);
		
//		    /* Now build the world pose using the attachment offset multiplied by the matrix of
//		       the base model bone we're attaching to.  As noted in
//		       $AnimationInDepth_AttachmentSection, you can use either your own matrix routines,
//		       or the provided Granny routine $ColumnMatrixMultiply4x3 to construct the Offset4x4
//		       matrix. */
//		    granny_matrix_4x4 Offset4x4;
//		    GrannyColumnMatrixMultiply4x3((granny_real32*)Offset4x4,
//		                                  (granny_real32*)AttachmentMatrix,
//		                                  (granny_real32*)BaseMatrix);
		
//		    GrannyBuildWorldPose(AttachSkeleton, 0, AttachSkeleton->BoneCount,
//		                         GlobalScene.SharedLocalPose,
//		                         (granny_real32*)Offset4x4,
//		                         GlobalScene.SharedWorldPose);
			
//			std::cout<<"Attachment Matrix: \n";
//			std::cout<<toAttach->meshes[0].grannyMesh->Name<<'\n';
//			for (int j=0; j<4; ++j) {
//				for (int k=0; k<4; ++k) {
//					std::cout<<AttachmentMatrix[j][k]<<' ';
//				}
//			}
//			std::cout<<'\n';
//			float *transform = GrannyGetWorldPose4x4( attachTo->worldPose, i );
//			std::cout<<"World Pose Matrix: \n";
//			std::cout<<toAttach->meshes[0].grannyMesh->Name<<'\n';
//			for (int j=0; j<16; ++j) {
//				std::cout<<transform[j]<<' ';
//			}
//			std::cout<<'\n';
//			granny_transform *gtransform = GrannyGetLocalPoseTransform(attachTo->localPose, i);
//			for (int j=0; j<17; ++j) {
//				std::cout<<((float *)gtransform)[j]<<' ';
//			}
			
			//std::cout<<"obbCenter "<<boneName<<"\n";
			
			glm::mat4 world = glm::inverse(glm::make_mat4((float *)&bone.InverseWorld4x4));
			obbCenter[0] = world[3][0];
			obbCenter[1] = world[3][1];
			obbCenter[2] = world[3][2];
			//obbCenter[0] = ((float *)AttachmentMatrix)[0];
			//obbCenter[1] = (float)fabs((float)((float *)AttachmentMatrix)[12]);
			//obbCenter[2] = ((float *)AttachmentMatrix)[3];
			
			//obbCenter[0] = ((float *)bone.InverseWorld4x4)[0];
			//obbCenter[1] = (float)fabs((float)(((float *)bone.InverseWorld4x4)[12]));
			//obbCenter[2] = ((float *)bone.InverseWorld4x4)[3];
			//obbCenter[0] = (bone.OBBMax[0] + bone.OBBMin[0])/2.0;
			//obbCenter[1] = (bone.OBBMax[1] + bone.OBBMin[1])/2.0;
			//obbCenter[2] = (bone.OBBMax[2] + bone.OBBMin[2])/2.0;
			return true;
		}
	}
	return false;
}

bool zGrannyGetObbCenter(std::string boneName, ZGrannyMesh *mesh, GLfloat obbCenter[3]) {
	if (mesh->grannyMesh == 0)
		return false;
	for (int i=0; i<mesh->grannyMesh->BoneBindingCount; ++i) {
		granny_bone_binding &bone = mesh->grannyMesh->BoneBindings[i];
		if (bone.BoneName == boneName) {
			std::cout<<"obbCenter "<<boneName<<"\n";
			obbCenter[0] = (bone.OBBMax[0] + bone.OBBMin[0])/2.0;
			obbCenter[1] = (bone.OBBMax[1] + bone.OBBMin[1])/2.0;
			obbCenter[2] = (bone.OBBMax[2] + bone.OBBMin[2])/2.0;
			return true;
		}
	}
	return false;
}

void zGrannyShutdownScene( ZGrannyScene *scene ) {
	for (int i=0; i<scene->modelCount; ++i) {
		ZGrannyModel &model = scene->models[i];
		for (int j=0; j<model.meshCount; ++j) {
			ZGrannyMesh &mesh = model.meshes[j];
			if (mesh.grannyBinding != 0) {
				GrannyFreeMeshBinding(mesh.grannyBinding);
			}
			if (mesh.grannyDeformer != 0) {
				GrannyFreeMeshDeformer(mesh.grannyDeformer);
			}
		}
		delete model.meshes;
		if (model.worldPose != 0) {
			GrannyFreeWorldPose(model.worldPose);
		}
		if (model.localPose != 0) {
			GrannyFreeLocalPose(model.localPose);
		}
		if (model.grannyInstance != 0) {
			GrannyFreeModelInstance(model.grannyInstance);
		}
	}
	delete scene->models;
	GrannyFreeFile( scene->loadedFile );
}

void zGrannyRenderScene(ZGrannyScene *scene, std::vector<GLuint > &textures, VertexRGB *vertexRgb, VertexRGB *vertexRgb2, GlShaderProgram *shaderProgram, GLfloat worldPos[3], renderInfo_t *renderInfo) {
	if (!scene->shouldRender) {
		return;
	}
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::ostringstream ss;
		ss<<"err19: "<<gluErrorString(err)<<'\n';
		std::cout<<ss.str()<<'\n';
	}
	if (shaderProgram != 0) {
		shaderProgram->use();
	}
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::ostringstream ss;
		ss<<"err20: "<<gluErrorString(err)<<' '<<shaderProgram->getProgram();
		std::cout<<ss.str()<<'\n';
	}
	if (worldPos != 0) {
		glPushMatrix();
		glTranslatef(worldPos[0], worldPos[1], worldPos[2]);
	}
	for( int i = 0; i < scene->modelCount; ++i ) {
		zGrannyRenderModel( scene, &scene->models[i], textures, vertexRgb, vertexRgb2, shaderProgram, renderInfo);
	}
	if (worldPos != 0) {
		glPopMatrix();
	}
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::ostringstream ss;
		ss<<"err6: "<<gluErrorString(err);
		std::cout<<ss.str()<<'\n';
	}
	if (shaderProgram != 0) {
		shaderProgram->unset();
	}
	if ((err = glGetError()) != GL_NO_ERROR) {
		std::ostringstream ss;
		ss<<"err7: "<<gluErrorString(err);
		std::cout<<ss.str()<<'\n';
	}
}
