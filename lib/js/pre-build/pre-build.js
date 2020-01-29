Module["ready"] = new Promise(res => {Module.onRuntimeInitialized = () => {res(Module)}});
  if (typeof module !== 'undefined') {
    module['exports'] = Module;
  }