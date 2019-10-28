if which emcc ; then
    emcc --bind lib/c++/src/tree-builder.binder.cpp -s WASM=1 -o lib/js/build/build.js
    sed -i '20 i Module.ready = new Promise(res => {Module.onRuntimeInitialized = () => {res(Module)}});' lib/js/build/build.js
    echo 'built'
else
    echo "emcc not found. If you have installed emscripten, navigate to you emskd folder and run '$source ./emsdk_env.sh', else see https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install"
fi
    