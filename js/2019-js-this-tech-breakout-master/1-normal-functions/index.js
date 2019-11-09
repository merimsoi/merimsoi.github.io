class Person {
  constructor(name) {
    this.name = name;
  }
  
  display() {
    console.log(this.name);
  }
}

/* * * * * * * * * * * * * * */

debugger;

var person = new Person('Jordan');

// #1
try {
  console.log('1. person.display():');
  person.display();
} catch (e) {
  console.error(e);
}

// #2
try {
  console.log('2. display():');
  const display = person.display;
  display();
} catch (e) {
  console.error(e);
}

// #3
function renderPerson1(person) {
  person.display();
}

try {
  console.log('3. renderPerson1(person):');
  renderPerson1(person);
} catch (e) {
  console.error(e);
}

// #4
function renderPerson2(display) {
  display();
}

try {
  console.log('4. renderPerson2(person.display):');
  renderPerson2(person.display);
} catch (e) {
  console.error(e);
}


/*****************************
 * Explicit Binding (.call)
 *****************************/

function renderThisName() {
  console.log(this.name);
}

// #5
try {
  console.log('5. renderThisName():');
  renderThisName();
} catch (e) {
  console.log(e);
}

// #6
try {
  console.log('6. renderThisName.call(person):');
  renderThisName.call(person);
} catch (e) {
  console.log(e);
}

// #7
const renderPersonName = renderThisName.bind(person);
try {
  console.log('7. renderPersonName():');
  renderPersonName();
} catch (e) {
  console.log(e);
}
