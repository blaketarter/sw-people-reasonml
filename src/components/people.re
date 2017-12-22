open ReasonReact;

type person = {
  name: string
};
type personList = list(person);
type state = {
  personList,
};

type action = 
  | AddPeople(personList);

let personListToComponents = (l: personList) => List.map((p) => <Person name=p.name />)(l);

let component = reducerComponent("People");
let make = (_children) => {
  ...component,
  initialState: () => { personList: [{ name: "Luke" }, { name: "Leia" }] },
  reducer: (action, _state) =>
    switch action {
      | AddPeople(personList) => Update({ personList: personList })
    },
  render: ({ state }) => {
    let people = personListToComponents(state.personList);

    <div>
      <h1>(stringToElement("Star Wars People"))</h1>
      (arrayToElement(Array.of_list(people)))
    </div>
  }
};
