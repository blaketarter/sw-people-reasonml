open ReasonReact;

let component = statelessComponent("Person");
let make = (~name: string, _children) => {
  ...component,
  render: (_self) => {
    <div>
      <p>(stringToElement(name))</p>
    </div>
  }
};
