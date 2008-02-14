<?xml version="1.0" encoding = "Windows-1252"?>
<VisualStudioProject
	ProjectType="Visual C++"
	Version="8.00"
	Name="oexlib"
	ProjectGUID="{7DA84DC2-D8AB-4DF4-8F8B-AC8C1A38E7AA}"
	SccProjectName=""
	SccLocalPath=""
	Keyword="Win32Proj">
	<Platforms>
		<Platform
			Name="Win32"/>
	</Platforms>
	<Configurations>
		<Configuration
			Name="Debug|Win32"
			OutputDirectory="Debug"
			IntermediateDirectory="oexlib.dir\Debug"
			ConfigurationType="4"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="FALSE"
			CharacterSet="2">
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions=" /Zm1000"
				AdditionalIncludeDirectories=""
				BasicRuntimeChecks="3"
				CompileAs="2"
				DebugInformationFormat="3"
				ExceptionHandling="1"
				InlineFunctionExpansion="0"
				Optimization="0"
				RuntimeLibrary="3"
				RuntimeTypeInfo="TRUE"
				WarningLevel="3"
				PreprocessorDefinitions="WIN32,_WINDOWS,_DEBUG,&quot;CMAKE_INTDIR=\&quot;Debug\&quot;&quot;"
				AssemblerListingLocation="Debug"
				ObjectFile="$(IntDir)\"
				ProgramDataBaseFileName="M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/../../bin/Debug/oexlib_d.pdb"
/>
			<Tool
				Name="VCCustomBuildTool"/>
			<Tool
				Name="VCResourceCompilerTool"
				AdditionalIncludeDirectories=""
				PreprocessorDefinitions="WIN32,_WINDOWS,_DEBUG,&quot;CMAKE_INTDIR=\&quot;Debug\&quot;&quot;"/>
			<Tool
				Name="VCMIDLTool"
				PreprocessorDefinitions="WIN32,_WINDOWS,_DEBUG,&quot;CMAKE_INTDIR=\&quot;Debug\&quot;&quot;"
				MkTypLibCompatible="FALSE"
				TargetEnvironment="1"
				GenerateStublessProxies="TRUE"
				TypeLibraryName="$(InputName).tlb"
				OutputDirectory="$(IntDir)"
				HeaderFileName="$(InputName).h"
				DLLDataFileName=""
				InterfaceIdentifierFileName="$(InputName)_i.c"
				ProxyFileName="$(InputName)_p.c"/>
			<Tool
				Name="VCManifestTool"
				UseFAT32Workaround="true"
			/>
			<Tool
				Name="VCPreBuildEventTool"/>
			<Tool
				Name="VCPreLinkEventTool"/>
			<Tool
				Name="VCPostBuildEventTool"/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="..\..\bin\$(OutDir)\oexlib_d.lib"/>
		</Configuration>
		<Configuration
			Name="Release|Win32"
			OutputDirectory="Release"
			IntermediateDirectory="oexlib.dir\Release"
			ConfigurationType="4"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="FALSE"
			CharacterSet="2">
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions=" /Zm1000"
				AdditionalIncludeDirectories=""
				CompileAs="2"
				ExceptionHandling="1"
				InlineFunctionExpansion="2"
				Optimization="2"
				RuntimeLibrary="2"
				RuntimeTypeInfo="TRUE"
				WarningLevel="3"
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;Release\&quot;&quot;"
				AssemblerListingLocation="Release"
				ObjectFile="$(IntDir)\"
				ProgramDataBaseFileName="M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/../../bin/Release/oexlib.pdb"
/>
			<Tool
				Name="VCCustomBuildTool"/>
			<Tool
				Name="VCResourceCompilerTool"
				AdditionalIncludeDirectories=""
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;Release\&quot;&quot;"/>
			<Tool
				Name="VCMIDLTool"
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;Release\&quot;&quot;"
				MkTypLibCompatible="FALSE"
				TargetEnvironment="1"
				GenerateStublessProxies="TRUE"
				TypeLibraryName="$(InputName).tlb"
				OutputDirectory="$(IntDir)"
				HeaderFileName="$(InputName).h"
				DLLDataFileName=""
				InterfaceIdentifierFileName="$(InputName)_i.c"
				ProxyFileName="$(InputName)_p.c"/>
			<Tool
				Name="VCManifestTool"
				UseFAT32Workaround="true"
			/>
			<Tool
				Name="VCPreBuildEventTool"/>
			<Tool
				Name="VCPreLinkEventTool"/>
			<Tool
				Name="VCPostBuildEventTool"/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="..\..\bin\$(OutDir)\oexlib.lib"/>
		</Configuration>
		<Configuration
			Name="MinSizeRel|Win32"
			OutputDirectory="MinSizeRel"
			IntermediateDirectory="oexlib.dir\MinSizeRel"
			ConfigurationType="4"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="FALSE"
			CharacterSet="2">
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions=" /Zm1000"
				AdditionalIncludeDirectories=""
				CompileAs="2"
				ExceptionHandling="1"
				InlineFunctionExpansion="1"
				Optimization="1"
				RuntimeLibrary="2"
				RuntimeTypeInfo="TRUE"
				WarningLevel="3"
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;MinSizeRel\&quot;&quot;"
				AssemblerListingLocation="MinSizeRel"
				ObjectFile="$(IntDir)\"
				ProgramDataBaseFileName="M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/../../bin/MinSizeRel/oexlib.pdb"
/>
			<Tool
				Name="VCCustomBuildTool"/>
			<Tool
				Name="VCResourceCompilerTool"
				AdditionalIncludeDirectories=""
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;MinSizeRel\&quot;&quot;"/>
			<Tool
				Name="VCMIDLTool"
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;MinSizeRel\&quot;&quot;"
				MkTypLibCompatible="FALSE"
				TargetEnvironment="1"
				GenerateStublessProxies="TRUE"
				TypeLibraryName="$(InputName).tlb"
				OutputDirectory="$(IntDir)"
				HeaderFileName="$(InputName).h"
				DLLDataFileName=""
				InterfaceIdentifierFileName="$(InputName)_i.c"
				ProxyFileName="$(InputName)_p.c"/>
			<Tool
				Name="VCManifestTool"
				UseFAT32Workaround="true"
			/>
			<Tool
				Name="VCPreBuildEventTool"/>
			<Tool
				Name="VCPreLinkEventTool"/>
			<Tool
				Name="VCPostBuildEventTool"/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="..\..\bin\$(OutDir)\oexlib.lib"/>
		</Configuration>
		<Configuration
			Name="RelWithDebInfo|Win32"
			OutputDirectory="RelWithDebInfo"
			IntermediateDirectory="oexlib.dir\RelWithDebInfo"
			ConfigurationType="4"
			UseOfMFC="0"
			ATLMinimizesCRunTimeLibraryUsage="FALSE"
			CharacterSet="2">
			<Tool
				Name="VCCLCompilerTool"
				AdditionalOptions=" /Zm1000"
				AdditionalIncludeDirectories=""
				CompileAs="2"
				DebugInformationFormat="3"
				ExceptionHandling="1"
				InlineFunctionExpansion="1"
				Optimization="2"
				RuntimeLibrary="2"
				RuntimeTypeInfo="TRUE"
				WarningLevel="3"
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;RelWithDebInfo\&quot;&quot;"
				AssemblerListingLocation="RelWithDebInfo"
				ObjectFile="$(IntDir)\"
				ProgramDataBaseFileName="M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/../../bin/RelWithDebInfo/oexlib.pdb"
/>
			<Tool
				Name="VCCustomBuildTool"/>
			<Tool
				Name="VCResourceCompilerTool"
				AdditionalIncludeDirectories=""
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;RelWithDebInfo\&quot;&quot;"/>
			<Tool
				Name="VCMIDLTool"
				PreprocessorDefinitions="WIN32,_WINDOWS,NDEBUG,&quot;CMAKE_INTDIR=\&quot;RelWithDebInfo\&quot;&quot;"
				MkTypLibCompatible="FALSE"
				TargetEnvironment="1"
				GenerateStublessProxies="TRUE"
				TypeLibraryName="$(InputName).tlb"
				OutputDirectory="$(IntDir)"
				HeaderFileName="$(InputName).h"
				DLLDataFileName=""
				InterfaceIdentifierFileName="$(InputName)_i.c"
				ProxyFileName="$(InputName)_p.c"/>
			<Tool
				Name="VCManifestTool"
				UseFAT32Workaround="true"
			/>
			<Tool
				Name="VCPreBuildEventTool"/>
			<Tool
				Name="VCPreLinkEventTool"/>
			<Tool
				Name="VCPostBuildEventTool"/>
			<Tool
				Name="VCLibrarianTool"
				OutputFile="..\..\bin\$(OutDir)\oexlib.lib"/>
		</Configuration>
	</Configurations>
	<Files>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt">
				<FileConfiguration
					Name="Debug|Win32">
					<Tool
					Name="VCCustomBuildTool"
					Description="Building Custom Rule M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/CMakeLists.txt"
					CommandLine="&quot;C:\Program Files\CMake 2.4\bin\cmake.exe&quot; -HM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8 -BM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8"
					AdditionalDependencies="M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeVS8FindMake.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystem.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeSystem.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystemSpecificInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeGenericSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\gcc.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\WindowsPaths.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeRCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.c.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCPlatform.cmake;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXPlatform.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Templates\CMakeWindowsSystemConfig.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;"
					Outputs="oexlib.vcproj.cmake"/>
				</FileConfiguration>
				<FileConfiguration
					Name="Release|Win32">
					<Tool
					Name="VCCustomBuildTool"
					Description="Building Custom Rule M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/CMakeLists.txt"
					CommandLine="&quot;C:\Program Files\CMake 2.4\bin\cmake.exe&quot; -HM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8 -BM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8"
					AdditionalDependencies="M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeVS8FindMake.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystem.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeSystem.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystemSpecificInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeGenericSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\gcc.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\WindowsPaths.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeRCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.c.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCPlatform.cmake;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXPlatform.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Templates\CMakeWindowsSystemConfig.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;"
					Outputs="oexlib.vcproj.cmake"/>
				</FileConfiguration>
				<FileConfiguration
					Name="MinSizeRel|Win32">
					<Tool
					Name="VCCustomBuildTool"
					Description="Building Custom Rule M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/CMakeLists.txt"
					CommandLine="&quot;C:\Program Files\CMake 2.4\bin\cmake.exe&quot; -HM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8 -BM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8"
					AdditionalDependencies="M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeVS8FindMake.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystem.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeSystem.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystemSpecificInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeGenericSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\gcc.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\WindowsPaths.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeRCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.c.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCPlatform.cmake;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXPlatform.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Templates\CMakeWindowsSystemConfig.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;"
					Outputs="oexlib.vcproj.cmake"/>
				</FileConfiguration>
				<FileConfiguration
					Name="RelWithDebInfo|Win32">
					<Tool
					Name="VCCustomBuildTool"
					Description="Building Custom Rule M:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8/CMakeLists.txt"
					CommandLine="&quot;C:\Program Files\CMake 2.4\bin\cmake.exe&quot; -HM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8 -BM:/Code/_temp/winglib/lib/oexlib/prj/win32_vs8"
					AdditionalDependencies="M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeVS8FindMake.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystem.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeSystem.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeSystemSpecificInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeGenericSystem.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\gcc.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\WindowsPaths.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeDetermineRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCCompiler.cmake.in&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeRCCompiler.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeRCInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestRCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CheckTypeSize.c.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCCompiler.cmake.in&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCXXInformation.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\Platform\Windows-cl.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCPlatform.cmake;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeFiles\CMakeCXXPlatform.cmake;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeCommonLanguageInclude.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Modules\CMakeTestCXXCompiler.cmake&quot;;&quot;C:\Program Files\CMake 2.4\share\cmake-2.4\Templates\CMakeWindowsSystemConfig.cmake&quot;;M:\Code\_temp\winglib\lib\oexlib\prj\win32_vs8\CMakeLists.txt;"
					Outputs="oexlib.vcproj.cmake"/>
				</FileConfiguration>
			</File>
		<Filter
			Name="Source Files"
			Filter="">
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\alloc.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\asso_list.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\circ_buf.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\data_packet.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\fifo_sync.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\file.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\find_files.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\md5.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\oex.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\parser.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\sys_time.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\unzip.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\zip.cpp">
			</File>
		</Filter>
		<Filter
			Name="Header Files"
			Filter="">
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\inc\alloc.h">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\inc\arb_delegates.h">
			</File>
		</Filter>
		<Filter
			Name="Windows OS Source Files"
			Filter="">
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\base_file.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\debug.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\event.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\fmap.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\hq_timer.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\ip_address.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\ip_socket.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\mem.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\mutex.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\sys.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\thread.cpp">
			</File>
			<File
				RelativePath="M:\Code\_temp\winglib\lib\oexlib\src\os\win32\tls.cpp">
			</File>
		</Filter>
	</Files>
	<Globals>
	</Globals>
</VisualStudioProject>
