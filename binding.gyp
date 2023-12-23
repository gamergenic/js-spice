{
  'variables': {
    "conditions": [
      ['OS=="linux"', {
      'project_root': '<!(pwd)',
      }],
      ['OS=="mac"', {
      'project_root': '<!(pwd)',
      }]
    ]
  },
  "targets": [
    {
      "target_name": "spice",
      "sources": [ 
        "src/source/spice.cpp",
        "src/source/azlrec.cpp",
        "src/source/bodvrd.cpp",
        "src/source/convrt.cpp",
        "src/source/cylrec.cpp",
        "src/source/dpr.cpp",
        "src/source/erract.cpp",
        "src/source/errdev.cpp",
        "src/source/errprt.cpp",
        "src/source/furnsh.cpp",
        "src/source/georec.cpp",
        "src/source/gfposc.cpp",
        "src/source/halfpi.cpp",
        "src/source/latrec.cpp",
        "src/source/pgrrec.cpp",
        "src/source/pi.cpp",
        "src/source/radrec.cpp",
        "src/source/recazl.cpp",
        "src/source/reccyl.cpp",
        "src/source/recgeo.cpp",
        "src/source/reclat.cpp",
        "src/source/recpgr.cpp",
        "src/source/recrad.cpp",
        "src/source/recsph.cpp",
        "src/source/rpd.cpp",
        "src/source/spd.cpp",
        "src/source/sphrec.cpp",
        "src/source/spkpos.cpp",
        "src/source/str2et.cpp",
        "src/source/timout.cpp",
        "src/source/twopi.cpp",
        "src/source/unload.cpp",
         ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "conditions": [

        ['OS=="win"', {
          "msvs_settings": {
            "VCCLCompilerTool": { "AdditionalOptions": [ "/EHsc" ],
            }
          },
          "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS', '_COMPLEX_DEFINED', 'MSDOS', 'OMIT_BLANK_CC', 'NON_ANSI_STDIO' ],
          "libraries": [ "cspice.lib" ],
          "link_settings": {
                'library_dirs': [
                    'src/cspice/x64/cspice/lib'
                ]
          },
          "include_dirs": [
            "<!@(node -p \"require('node-addon-api').include\")",
            "src/cspice/x64/cspice/include",
            "src/include"
          ],
        }],

        
        ['OS=="linux"', {
          "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS', 'NON_UNIX_STDIO' ],
          "libraries": [ "<(project_root)/src/cspice/linux/cspice/lib/cspice.a" ],
          "link_settings": {
                'library_dirs': [
                    '<(project_root)/src/cspice/linux/cspice/lib'
                ]
          },
          "include_dirs": [
            "<!@(node -p \"require('node-addon-api').include\")",
            "src/cspice/linux/cspice/include",
            "src/include"
          ],
        }],

        
        ['OS=="mac"', {
          "defines": [ 'NAPI_DISABLE_CPP_EXCEPTIONS', 'NON_UNIX_STDIO' ],
          "libraries": [ "<(project_root)/src/cspice/linux/cspice/lib/cspice.a" ],
          "link_settings": {
                'library_dirs': [
                    'src/cspice/osx/cspice/lib'
                ]
          },
          "include_dirs": [
            "<!@(node -p \"require('node-addon-api').include\")",
            "src/cspice/osx/cspice/include",
            "src/include"
          ],
        }],


      ]
    }
  ]
}
