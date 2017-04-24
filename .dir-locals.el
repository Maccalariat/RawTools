(
 (
  nil . (
		 (tab-width . 4)
		 (indent-tab-mode . t)
		 (projectile-project-name "RawTools")		 
		 )
	  )
 
 (c++-mode . (
			  (c-basic-offset . 4)
			  (tab-width . 4)
			  (indent-tabs-mode . t)
			  (eval (lambda ()
					  (setq my-cores (numcores))
					  (setq compile-command (concat "cmake --build " (projectile-project-root) "build-debug --config Debug -- -j" (number-to-string my-cores)))))
			  
			  (company-clang-arguments . ("-std=c++14"
										  "-fno-ms-compatibility"
										  "-IE:/projects/cpp/RawTools/RawToolsLib/include"
										  "-IE:/projects/cpp/RawTools/RawToolslib/src"
										  "-ID:/MinGW64Toolchain/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++"
										  "-ID:/MinGW64Toolchain/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/x86_64-w64-mingw32"
										  "-ID:/MinGW64Toolchain/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/6.3.0/include/c++/backward"
										  "-ID:/MinGW64Toolchain/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/6.3.0/include"
										  "-ID:/MinGW64Toolchain/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/6.3.0/include-fixed"
										  "-ID:/MinGW64Toolchain/mingw64/bin/../lib/gcc/x86_64-w64-mingw32/6.3.0/../../../../x86_64-w64-mingw32/include"))
			  )
		   )
 )
