Module["ready"] = new Promise(res => {Module.onRuntimeInitialized = () => {res(Module)}});