//This is Modev configuration file
	/*
		Rules:
			Each properties has a maximum name of 16 characters including "m_" starters.
			Always have "m_" at the start to avoid confusion to other libs.
	*/

//Constant properties
	/*
		These are official Modev properties which is set by Andrew Dexembre.
		It's not ideal to touch it
	*/
#define m_VersionMajorValue	0
#define m_VersionMinorValue	0
#define m_VersionPatchValue	0
#define m_VersionName		"Succulent"

//Distro properties
	/*
		Ok now you can touch
		These are custom Modev's distro properties that you can set if you plan to make a branch of Modev
	*/
#define m_DistroID			""	/*Leave empty if this is not a branch*/
#define m_DistVerMajorValue	0
#define m_DistVerMinorValue	0
#define m_DistVerPatchValue	0
#define m_DistVerName		""

//General properties
#define m_ScriptSize		1024*16
#define m_UnderConstruction	true

//Automatic properties
	//Compile time utilities
	#define STR_IMPL(x) #x
	#define STR(x) STR_IMPL(x)
	/*
		You don't even need to touch these,
		these are automatically calculated upon compile time.
		The only thing you need to know is it does exist
	*/
#define m_VersionValue		m_VersionMajorValue*1000+m_VersionMinorValue*100+m_VersionPatchValue
#define m_VersionString		STR(m_VersionMajorValue)"."STR(m_VersionMinorValue)"."STR(m_VersionPatchValue)

#define m_DistVerValue		m_DistVerMajorValue*1000+m_DistVerMinorValue*100+m_DistVerPatchValue
#define m_DistVerString		STR(m_DistVerMajorValue)"."STR(m_DistVerMinorValue)"."STR(m_DistVerPatchValue)

#ifdef ARDUINO
	#define m_Emulation		false
#else
	#define m_Emulation		true
#endif