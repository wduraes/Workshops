## Basic MQTT with Adafruit IO

Adafruit IO implements a MQTT broker which can be used for tests and learning purposes. While nothing prevents us from using it for more advanced scenarios and professional use, this platform lacks more advanced resources like scalability, longer term storage, device identity, provisioning and etc.

### Step 1 - Create your account

Visit https://io.adafruit.com and create your account. It is free. there is a paid version as well and, as per Oct 2022 the paid version costs $10 per month for double the datapoints and days of storage.

### Step 2 - Create a topic

We need topics (Adafruit call them feeds) so we can publish data to. You can create up to 10 topics/feeds with a free subscription.

1. Navigate to `Feeds` (top menu)
2. Click on the `New Feed` button
3. Add a name `Test`
4. There is no need for description, but feel free to add one
5. Your new topic should show in the topic list

### Step 3 - Create a Dashboard

Dashboards organize MQTT topics and its information in a visual way allowing you to interact with the topics/feeds by either reading or writing values to them.

1. Navigate to `Dashboards` (top menu)
2. Click on the `New Dashboard` button
3. Add a name `Test`
4. There is no need for description, but feel free to add one
5. Your new topic should show in the topic list
6. Click on the feed name and you should see the empty Dashboard you just created

### Step 4 - Connect it all

In this step you'll create blocks in the dashboard to interact with your `test` topic/feed. The diagram below shows this interaction:

![Toolchain](../Images/mqtt.png)

#### Create a button

1. Open `Dashboard Settings` (the cogwheel icon at the top right)
1. Click on `+ Create a new Block`
1. Select `Momentary Button` which is teh second icon (the blue button which says RESET)
1. In the `Connect a Feed` dialog, select the topic `Test` and click `Next Step` at the bottom right of the page
1. In the `Block Settings` dialog, add “Test” to the Button Text
1. Leave “Press Value” as 1
1. Leave “Release Value” as 0
1. Click `Create block`

At this point, you should be back to the dashboard, and you can see there is a button with the label that says Test.

Every time you hit the button `Test` a message will be published to the topic name Test.

#### Create a Stream to test your Topic

1. Once again, open `Dashboard Settings` (the cogwheel icon at the top right)
1. Click on `+ Create a new Block`
1. Select `Stream` (the sixth icon)
1. Select the topic `Test` and click `Next Step` at the bottom right of the page
1. Add `Test Feed` to the block title
1. Select NO for `Show group name`
1. Select NO for `Show feed name`
1. Click `Create block`

Like before, at this point you should be back to the dashboard, and you can see there is a button and the `Test Feed` stream block.

To test it, click on the button to see the message appearing in the stream block.

#### More to explore

Feel free to explore all 19 types of blocks available, I'm sure you'll find something interesting or something you can use in a future project!

Almost all of them can be used to either read from a topic/feed or to write to a topic/feed.

![Toolchain](../Images/blocks.png)