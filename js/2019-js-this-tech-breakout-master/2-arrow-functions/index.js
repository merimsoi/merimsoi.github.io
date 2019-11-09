class Person {
  constructor(name) {
    this.name = name;

    this.display = () => {
      console.log(this.name);
    }
  }
}

/* * * * * * * * * * * * * * */

debugger;

var person = new Person('Jordan!');

// #1
try {
  console.log('1. ARROW person.display():');
  person.display();
} catch (e) {
  console.error(e);
}

// #2
try {
  console.log('2. ARROW display():');
  const display = person.display;
  display();
} catch (e) {
  console.error(e);
}

// #3
function renderArrowPerson1(person) {
  person.display();
}

try {
  console.log('3. ARROW renderArrowPerson1(person):');
  renderArrowPerson1(person);
} catch (e) {
  console.error(e);
}

// #4
function renderArrowPerson2(display) {
  display();
}

try {
  console.log('4. ARROW renderArrowPerson2(person.display):');
  renderArrowPerson2(person.display);
} catch (e) {
  console.error(e);
}
