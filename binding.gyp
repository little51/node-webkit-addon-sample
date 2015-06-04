{
  "targets": [
    {
      "target_name": "localproxy",
      "sources": [ "localproxy.cc" ],
	  "include_dirs": ["include"],
      "libraries": ["-l../library/lib_json.lib"],
	  "msvs_disabled_warnings": [ 4244,4005,4506,4345,4804 ],
	}	
  ]
}