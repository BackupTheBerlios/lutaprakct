
class Node: public Orient 
{
	Node				*Next;
//	CrtInstanceCamera	*InstanceCamera;	// REFACTOR IN PROGRESS needs to support multiple instances
//	CrtInstanceLight	*InstanceLight;		// REFACTOR IN PROGRESS needs to support multiple instances
//	CrtInstanceLight	*nearistInstanceLight;
//	CrtGeometry			*Geometry;			// REFACTOR IN PROGRESS needs to support multiple instances
//	CrtAnimation		*Animations[MAX_ANIMS];
	int				NumAnimations; 
	Node				*Parent; 
	Node				*Children;
	int			NumChildren;
	bool				UsedForSkinning; 
	bool				InverseBindMatrixReady; 
	bool 			OrientReady;
	int				Idx; 
	int				ParentIdx; 
	int				Depth; 
public:
//	std::vector <CrtInstanceCamera *> InstanceCameras;  
	std::vector <InstanceGeometry *> InstanceGeometries;  
//	std::vector <CrtInstanceController *> InstanceControllers;
//	std::vector <CrtInstanceLight *> InstanceLights;

public:

	Node():
	  Next(NULL),
	  NearistInstanceLight(NULL),
	  NumAnimations(0),
	  Parent(NULL),
	  Children(NULL),
	  NumChildren(0),
	  UsedForSkinning(CrtFalse),
	  InverseBindMatrixReady(CrtFalse),
	  OrientReady(CrtFalse),
	  Idx(-1),
	  ParentIdx(-1),
	  Depth(0)
	{
		Name[0] = 0;
		Id[0] = 0;
		Sid[0] = 0;
	}

	~CrtNode()
	{
		Destroy(); 
	}


	void	Destroy()
	{
		// need to delete any children or siblings
		if (Children)
			CrtDelete( Children ); 		
		if (Next)
			CrtDelete( Next ); 
	}


protected:
	friend class CrtScene; 
	//friend class CrtSkin;

	inline	Node	*SetNext( Node * next )	{ Next = next; return this;}
	inline	void	SetName( const char * n ){ CrtCpy(Name, n); }
	inline	void	SetId( const charhar * n ){ CrtCpy(Id, n); }
	inline	void	SetSid( const char * n ){ CrtCpy(Sid, n); }
	inline	void	SetParent( Node * node)	{ Parent = node; };

	void	SetChild( Node * );
	void	AddObjectReference( char * name ); 	

	void	AddChild( Node * node )
	{
		if (!Children )
		{
			Children = node; 
		}
		else
		{
			node->SetNext( Children ); 
			Children = node; 
		}
		NumChildren++; 

	}

//	inline	void	SetGeometry( CrtGeometry * geo ) { Geometry = geo; }
	//inline	void	SetAnimation( CrtAnimation * anim ) { Animations[NumAnimations] = anim; NumAnimations++; }
	//inline	void	SetUsedForSkinning() { UsedForSkinning = CrtTrue; } 
	inline	void	SetIdx( int id ){ Idx = id; }
	inline	void	SetParentIdx( int id ){ Idx = id; }
	//inline	void	SetInverseBindMatrix( CrtMatrix imat )
	//{
		memcpy( InverseBindMatrix, imat, sizeof( CrtMatrix ) ) ; 
	//	InverseBindMatrixReady = CrtTrue; 
	//}
	
	void	DrawLineToChildren(); 
	

public:

	//---------------------- External Interfaces ---------------------------------//	
	// After you get the SceneRoot from the CrtScene.GetSceneRoot 
	// got throught he nodes and just check the type 
	// if the type is Crt_Geo the GetGeometry(); 
	// from there you will need to get the GeoGroups which will contain the materials,
	// Points, Normals, and the rest of the Geo data.  
	// To get the next sibling it's simply node = node->GetNext();  
	// until the node is null.  
	// Node there may also be animation attached to the node as well as geometry
	// so Do a GetAnimation to check for animation attached.  If not null try and get 
	// the Animation keys.  
	// Currently Animation refactoring isn't done but hope to have that completed soon. 
	// Finaly to get the orient check CrtData.h CrtOrient definition.  It describes 
	// how to handle getting a camera orient verse getting a regular node orient.  

	inline	Node		*	GetNext() { return Next; }
	inline	char		*	GetName(){ return Name; }
	inline	char		*	GetId(){ return Id; }
	inline	char		*	GetSid(){ return Sid; }
//	inline	CrtNode		*	GetParent(){ return Parent; }
	inline	Node		*	GetChild(){ return Children; }
	
//	inline	CrtGeometry *	GetGeometry(){ return Geometry; }
	inline	int			GetNumAnimations(){ return NumAnimations; } 
//	inline	CrtAnimation*	GetAnimation( CrtInt i){return Animations[i]; }
	inline	int			GetIdx(){ return Idx; } 
//	inline	CrtInt			GetParentIdx(){ return ParentIdx; }
	inline  int			GetDepth(){ return Depth; }
	inline  bool			GetIsUsedForSkinning(){ return UsedForSkinning; } 
		
	inline	iInt		GetNumChildren()
	{
		int	num = 0; 
		Node * child = Children; 
		while( child )
		{
			num++;
			child = child->GetNext(); 
		}
		return num; 
	}

/*	inline void 		SetDepth()
	{
		Depth = 1; 
		CrtNode * par = Parent; 
		while ( par )
		{
			Depth++; 
			par = par->GetParent(); 
		}
	}
*/
//	CrtNode		*   GetNode( CrtChar * node ); 
//	CrtNode		*   GetNode( CrtInt nodeIdx ); 
	void	Update( float time);
	void	UpdateOrient( float time); 
	void	BuildLWMatrix( float time );
	void	Render(); 	

};