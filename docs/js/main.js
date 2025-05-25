
class UIIndex extends HTMLElement {
  constructor(){
    super();
    addEventListener("DOMContentLoaded", ()=>this.update());
  }
  connectedCallback(){
    this.update();
  }
  update(){
    this.innerHTML = '<h1>Index</h1>';
    const sections = [];
    for(const section of document.querySelectorAll("section")){
      let last;
      while(sections.at(-1) && !sections.at(-1).element.contains(section))
        last = sections.pop();
      if(!last){
        last = {
          index: 0,
          element: this,
          ul: document.createElement("ul"),
        };
      }
      if(sections.at(-1)?.element !== section){
        const ul = document.createElement("ul");
        (sections.at(-1)?.ul||this).appendChild(ul);
        sections.push({
          element: section,
          index: last.index+1,
          ul,
        });
      }
      const current = sections.at(-1);
      const index = sections.slice(1).map(x=>x.index+'.').join('');
      const entry = section.children[0];
      if(!(entry instanceof HTMLHeadingElement))
        continue;
      const li = document.createElement("li");
      const a = document.createElement("a");
      li.appendChild(a);
      a.appendChild(document.createTextNode(index + ' ' + entry.textContent));
      if(entry.id)
        a.href = '#'+entry.id;
      (current?.ul||this).appendChild(li);
    }
  }
};
customElements.define("ui-index", UIIndex);
