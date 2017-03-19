#ifndef PROJECT_RAWTOOLS_H_H
#define PROJECT_RAWTOOLS_H_H



class RawTools {
	public:
	RawTools();
	~RawTools();

	// public methods
	void getMetaData();
	void getBeyer();
	void getInterpolated();
	void getPostProcesed();

	private:
	class RawToolsImpl;					// forward declaration
	std::unique_ptr<RawToolsImpl>pimpl;
}
#endif // PROJECT_RAWTOOLS_H_H

