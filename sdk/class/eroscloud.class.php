<?php
	class eroscloud {
		private $projectName = null;
		private $projectFolder = null;
		
		public function createClass($className, $projectPath) {
			// Copy example files
			copy("../template/ErosServletExample.h", $projectPath . "/src/" . $className . ".h");
			copy("../template/ErosServletExample.cpp", $projectPath . "/src/" . $className . ".cpp");

			// Rename Classes
			$_h = file_get_contents($projectPath . "/src/" . $className . ".h");
			$_cpp = file_get_contents($projectPath . "/src/" . $className . ".cpp");
			$_makefile = file_get_contents($projectPath . "/makefile");

			$_h = str_replace("ErosServletExample", $className, $_h);
			$_h = str_replace("EROSSERVLETEXAMPLE", $className, $_h);

			$_cpp = str_replace("ErosServletExample", $className, $_cpp);

			echo $_makefile . "\n";
			$_makefile .= "\n\tg++ -fPIC -shared res/ErosServlet.h src/$className.h src/$className.cpp -o war/$className.so";
			echo $_makefile . "\n";
			
			file_put_contents($projectPath ."/src/" . $className . ".h", $_h);
			file_put_contents($projectPath ."/src/" . $className . ".cpp", $_cpp);

			file_put_contents($projectPath ."/makefile", $_makefile);
		}
		
		public function createProject($projectName, $projectFolder) {
			$projectPath = $projectFolder . $projectName;
			if (mkdir($projectPath)) {
				echo $projectPath . "\n";
			}
			if (mkdir($projectPath . '/src')) {
				echo $projectPath . "/src\n";
			}
			if (mkdir($projectPath . '/res')) {
				echo $projectPath . "/res\n";
			}
			if (mkdir($projectPath . '/lib')) {
				echo $projectPath . "/lib\n";
			}
			if (mkdir($projectPath . '/war')) {
				echo $projectPath . "/war\n";
			}

			// Copy resouece files
			copy("../res/ErosRequest.h", $projectPath . "/res/ErosRequest.h");
			copy("../res/ErosResponse.h", $projectPath . "/res/ErosResponse.h");
			copy("../res/ErosServlet.h", $projectPath . "/res/ErosServlet.h");

			copy("../template/makefile", $projectPath . "/makefile");
			copy("../template/ErosServletExample.h", $projectPath . "/src/ErosServletExample.h");
            copy("../template/ErosServletExample.cpp", $projectPath . "/src/ErosServletExample.cpp");

			$this->createClass($projectName, $projectPath);
		}
	}
?>
