#ifndef PROJECT_RAWTOOLS_H_H
#define PROJECT_RAWTOOLS_H_H
#include <memory>
	/// the public API for RawTools
	/// This is a 'primitive' collection of atomic api calls on an unsuspecting raw file
	/// The typical processing sequence is:
	/// 1. getMetaData (this is required as the first step
	/// 2. GetBeyer (this retrieves the colour channel information
	/// 3. getInterpolated (this interpolates the image)
class RawTools {
	public:
	RawTools();
	~RawTools();
	RawTools(RawTools&& op ) noexcept;
	RawTools& operator=(RawTools&& op ) noexcept;

	// public methods
    void setFile(std::string& fileName);
	void getMetaData();
	void getBeyer();
	void getInterpolated();
	void getPostProcesed();
    void writeFile(const std::string& fileName);


	private:
	class RawToolsImpl;					// forward declaration
	std::unique_ptr<RawToolsImpl>pImpl;
};
#endif // PROJECT_RAWTOOLS_H_H

