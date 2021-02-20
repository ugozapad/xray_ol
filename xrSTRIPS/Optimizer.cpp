#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////////////////////
// NextIsCW()
//
// Returns true if the next face should be ordered in CW fashion
//
bool CNvTriStripDlg::NextIsCW(const int numIndices)
{
	return ((numIndices % 2) == 0);
}


///////////////////////////////////////////////////////////////////////////////////////////
// IsCW()
//
// Returns true if the face is ordered in CW fashion
//
bool CNvTriStripDlg::IsCW(NvFaceInfo *faceInfo, int v0, int v1)
{
	if (faceInfo->m_v0 == v0)
		return (faceInfo->m_v1 == v1);
	
	else if (faceInfo->m_v1 == v0)
		return (faceInfo->m_v2 == v1);
	
	else 
		return (faceInfo->m_v0 == v1);
	
	// shouldn't get here
	assert(0);
	return false;
}


//used in CreateStrips
template<class T> 
inline void SWAP(T& first, T& second) 
{
	T temp = first;
	first = second;
	second = temp;
}

///////////////////////////////////////////////////////////////////////////////////////////
// CreateStrips()
//
// Up until now, the strips had been strips at heart, but tri lists in reality.
// Now, remove redundant indices, and stitch together strips to form one, huge uber-strip
//  using degenerate tris.
//
void CNvTriStripDlg::CreateStrips()
{
	NvFaceInfo tLastFace(0, 0, 0);
	int nStripCount = strips.size();
	assert(nStripCount > 0);

	for (int i = 0; i < nStripCount; i++)
	{
		NvStripInfo *strip = strips[i];
		int nStripFaceCount = strip->m_faces.size();
		int stripIndicesSize = stripIndices.size();
		assert(nStripFaceCount > 0);

		// Handle the first face in the strip
		{
			NvFaceInfo tFirstFace(strip->m_faces[0]->m_v0, strip->m_faces[0]->m_v1, strip->m_faces[0]->m_v2);

			// If there is a second face, reorder vertices such that the
			// unique vertex is first
			if (nStripFaceCount > 1)
			{
				int nUnique = NvStripifier::GetUniqueVertexInB(strip->m_faces[1], &tFirstFace);
				if (nUnique == tFirstFace.m_v1)
				{
					SWAP(tFirstFace.m_v0, tFirstFace.m_v1);
				}
				else if (nUnique == tFirstFace.m_v2)
				{
					SWAP(tFirstFace.m_v0, tFirstFace.m_v2);
				}

				// If there is a third face, reorder vertices such that the
				// shared vertex is last
				if (nStripFaceCount > 2)
				{
					int nShared = NvStripifier::GetSharedVertex(strip->m_faces[2], &tFirstFace);
					if (nShared == tFirstFace.m_v1)
					{
						SWAP(tFirstFace.m_v1, tFirstFace.m_v2);
					}
				}
			}

			if (i != 0)
			{
				// Double tap the first in the new strip
				stripIndices.push_back(tFirstFace.m_v0);

				// Check CW/CCW ordering
				if (NextIsCW(stripIndices.size()) != IsCW(strip->m_faces[0], tFirstFace.m_v0, tFirstFace.m_v1))
				{
					stripIndices.push_back(tFirstFace.m_v0);
				}
			}
			else
			{
				if(!IsCW(strip->m_faces[0], tFirstFace.m_v0, tFirstFace.m_v1))
					stripIndices.push_back(tFirstFace.m_v0);
			}

			stripIndices.push_back(tFirstFace.m_v0);
			stripIndices.push_back(tFirstFace.m_v1);
			stripIndices.push_back(tFirstFace.m_v2);

			// Update last face info
			tLastFace = tFirstFace;
		}

		for (int j = 1; j < nStripFaceCount; j++)
		{
			int nUnique = NvStripifier::GetUniqueVertexInB(&tLastFace, strip->m_faces[j]);
			if (nUnique != -1)
			{
				stripIndices.push_back(nUnique);

				// Update last face info
				tLastFace.m_v0 = tLastFace.m_v1;
				tLastFace.m_v1 = tLastFace.m_v2;
				tLastFace.m_v2 = nUnique;
			}
		}

		// Double tap between strips.
		stripIndices.push_back(tLastFace.m_v2);

		// Update last face info
		tLastFace.m_v0 = tLastFace.m_v1;
		tLastFace.m_v1 = tLastFace.m_v2;
		tLastFace.m_v2 = tLastFace.m_v2;
	}
}


