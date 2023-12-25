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
      "target_name": "js-spice",
      "sources": [ 
        "src/source/js-spice.cpp",
        "src/source/utility/err.cpp",
        "src/source/utility/pack.cpp",
        "src/source/utility/unpack.cpp",
        "src/source/wrapped/axisar.cpp",
        "src/source/wrapped/azlrec.cpp",
        "src/source/wrapped/bodvrd.cpp",
        "src/source/wrapped/convrt.cpp",
        "src/source/wrapped/cylrec.cpp",
        "src/source/wrapped/dpr.cpp",
        "src/source/wrapped/erract.cpp",
        "src/source/wrapped/errdev.cpp",
        "src/source/wrapped/errprt.cpp",
        "src/source/wrapped/furnsh.cpp",
        "src/source/wrapped/georec.cpp",
        "src/source/wrapped/gfposc.cpp",
        "src/source/wrapped/halfpi.cpp",
        "src/source/wrapped/ident.cpp",
        "src/source/wrapped/latrec.cpp",
        "src/source/wrapped/mxm.cpp",
        "src/source/wrapped/mxv.cpp",
        "src/source/wrapped/pgrrec.cpp",
        "src/source/wrapped/pi.cpp",
        "src/source/wrapped/radrec.cpp",
        "src/source/wrapped/recazl.cpp",
        "src/source/wrapped/reccyl.cpp",
        "src/source/wrapped/recgeo.cpp",
        "src/source/wrapped/reclat.cpp",
        "src/source/wrapped/recpgr.cpp",
        "src/source/wrapped/recrad.cpp",
        "src/source/wrapped/recsph.cpp",
        "src/source/wrapped/rpd.cpp",
        "src/source/wrapped/spd.cpp",
        "src/source/wrapped/sphrec.cpp",
        "src/source/wrapped/spkpos.cpp",
        "src/source/wrapped/str2et.cpp",
        "src/source/wrapped/timout.cpp",
        "src/source/wrapped/twopi.cpp",
        "src/source/wrapped/unload.cpp",
        "src/source/wrapped/xpose.cpp",
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
