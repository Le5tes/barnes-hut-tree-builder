if which emcc ; then
    emcc lib/c++/src/tree-builder.cpp -o lib/js/build/build.js
else
    echo "emcc not found. If you have installed emscripten, navigate to you emskd folder and run '$source ./emsdk_env.sh', else see https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install"
fi
    