# Basic form-builder example

```html
<exp-form-builder
    [formConfig]="basicForm"
    [name]="basic-form"
></exp-form-builder>
```

`formConfig` is a json object.
`name` is a string object.

```
basicForm: {
    form: {
        classes: 'any css classes',
        fields: [
            {
                type: 'text',
                label: 'Store ID',
                name: 'store_id',
                placeholder: 'Enter your store id number',
                classes: 'any classes for the field',
                label_classes: 'any classes for the label',
                layout_classes: 'layout classes',
                block_classes: 'block classes',
                validation: [
                    {
                        rule: 'required',
                        message: 'Store ID field is required!',
                    },
                ],
            },
            {
                type: 'email',
                label: 'Email',
                name: 'j_username',
                placeholder: 'Enter your email address',
                classes: 'full-width _sans-serif',
                label_classes: 'label-black',
                layout_classes:
                    'smallest _uppercase _bold _mb-xxxs',
                block_classes: 'email-box mt0',
                validation: [
                    {
                        rule: 'required',
                        message: 'Email field is required!',
                    },
                    {
                        rule: 'email',
                        message: 'Enter a valid email',
                    },
                ],
            },
            {
                type: 'password',
                label: 'Password',
                name: 'j_password',
                placeholder: 'Enter your password',
                classes: 'full-width _sans-serif',
                label_classes: 'label-black',
                layout_classes:
                    'smallest _uppercase _bold _mb-xxxs',
                block_classes: 'password-box mt0',
                validation: [
                    {
                        rule: 'required',
                        message: 'Password field is required!',
                    },
                ],
            },
        ],
        action_buttons: {
            classes: 'flex mt2',
            buttons: [
                {
                    text: 'Sign In',
                    action: 'submit',
                    classes:
                        'btn-white-blue btn _sans-serif login-btn _bold',
                },
            ],
        },
    },
},
```

####other supported keys for a field:
`required` (true of false), shortcut for the required validation rule.

`default_value` set a default value for the field.

`options` (for radio-group type), example:

```
options: [
    { label: 'Yes', value: 'yes' },
    { label: 'No', value: 'no' },
],
```

`check_disabled` allows to make a field disabled based on another field's value as follows:

```
check_disabled: {
    controller_name: 'some_fields_name',
    controller_value: 'desired_value',
},
```

`context_value` allows to set the value of a field from the context, example:

```
context_value: {
    context: 'page', // or 'app'
    key: 'currentUser.desiredKey',
    condition: { // optional, if we only want to set the value conditonally
        controller_name: 'some_fields_name',
        controller_value: 'desired_value',
    },
},
```

`maskConfig` to provide a mask for the field (useful for phone or ssn numbers).
example:

```
maskConfig: {
   keepCharPositions: false,
   showMask: true,
   guide: false,
   placeholderChar: '_',
   mask: [
       /\d/,
       /\d/,
       /\d/,
       '-',
       /\d/,
       /\d/,
       '-',
       /\d/,
       /\d/,
       /\d/,
       /\d/,
   ],
},
```

###list of supported field types:

text, password, email, date, select, radio-group, checkbox

###list of supported validation rules:

required, email, regexp, async, ageMax, ageMin, ssn, equal
