if which emcc ; then
    if [ ! -d "lib/js/core" ]; then
      mkdir lib/js/core
    fi

    emcc --bind lib/c++/src/tree-builder.binder.cpp --pre-js lib/js/pre-build/pre-build.js -s ALLOW_MEMORY_GROWTH=1 -s ENVIRONMENT=node -Os -s WASM=1 -o lib/js/core/build.js
    BUILD_STATUS=$?
    
    if [ $BUILD_STATUS != '0' ]
    then 
        echo 'build failed'
        exit 1
    fi
    
    echo 'built'
else
    echo "emcc not found. If you have installed emscripten, navigate to you emskd folder and run '$source ./emsdk_env.sh', else see https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install"
    exit 1;
fi
    